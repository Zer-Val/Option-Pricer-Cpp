import yfinance as yf
import numpy as np
import matplotlib.pyplot as plt
import itertools
import pandas as pd

def download_data(ticker, start, end):
    data = yf.download(ticker, start=start, end=end, auto_adjust=True)
    data = data[['Close']].dropna()
    data.columns = ['Price']
    return data

def calculate_spread(series1, series2):
    spread = series1 - series2
    return spread

def plot_pair_trading(series1, series2, spread, portfolio_value, title_suffix=""):
    plt.figure(figsize=(14, 14))

    plt.subplot(4, 1, 1)
    series1.plot(label='Instrument 1')
    series2.plot(label='Instrument 2')
    plt.title(f'Prix des deux actifs {title_suffix}')
    plt.xlabel('Date')
    plt.ylabel('Prix')
    plt.legend()

    plt.subplot(4, 1, 2)
    spread.plot(color='purple')
    plt.axhline(spread.mean(), color='black', linestyle='--', label='Moyenne du spread')
    plt.legend()
    plt.title(f'Spread entre les deux actifs {title_suffix}')
    plt.xlabel('Date')
    plt.ylabel('Spread')

    plt.subplot(4, 1, 3)
    (portfolio_value / portfolio_value.iloc[0]).plot(color='green')
    plt.title(f'Performance relative de la stratégie {title_suffix}')
    plt.xlabel('Date')
    plt.ylabel('Multiplicateur')

    plt.subplot(4, 1, 4)
    portfolio_value.plot(color='blue')
    plt.title(f'Valeur absolue du portefeuille {title_suffix}')
    plt.xlabel('Date')
    plt.ylabel('Valeur (€)')

    plt.tight_layout()
    plt.show()

def calculate_sharpe_ratio(returns, risk_free_rate=0):
    excess_returns = returns - risk_free_rate / 252
    sharpe_ratio = np.sqrt(252) * excess_returns.mean() / excess_returns.std()
    return sharpe_ratio

def backtest_with_thresholds(spread, entry_threshold=1.0, exit_threshold=0.0, initial_capital=1000):
    mean = spread.mean()
    std = spread.std()
    z_score = (spread - mean) / std

    position = np.where(z_score > entry_threshold, -1, np.where(z_score < -entry_threshold, 1, 0))
    position = np.where(abs(z_score) < exit_threshold, 0, position)
    position = pd.Series(position, index=spread.index).ffill().fillna(0)

    daily_pnl = position.shift(1) * spread.diff().fillna(0)
    portfolio_value = initial_capital + daily_pnl.cumsum()

    returns = daily_pnl / portfolio_value.shift(1).fillna(initial_capital)

    return portfolio_value, returns

def optimize_thresholds(spread, initial_capital=1000):
    best_perf = -np.inf
    best_entry = None
    best_exit = None
    best_portfolio_value = None
    best_returns = None

    for entry in np.arange(0.5, 2.5, 0.1):
        for exit in np.arange(0.0, 0.5, 0.1):
            portfolio_value, returns = backtest_with_thresholds(spread, entry_threshold=entry, exit_threshold=exit, initial_capital=initial_capital)
            final_perf = portfolio_value.iloc[-1]

            if final_perf > best_perf:
                best_perf = final_perf
                best_entry = entry
                best_exit = exit
                best_portfolio_value = portfolio_value
                best_returns = returns

    return best_entry, best_exit, best_portfolio_value, best_returns

def main():
    tickers = {"Orge": "C", "Blé": "ZW=F", "Maïs": "ZC=F", "Soja": "ZS=F"}
    start_date = "2020-01-01"
    end_date = "2024-01-01"
    initial_capital = 1000

    data = {}
    for name, ticker in tickers.items():
        print(f"Téléchargement des données pour {name}...")
        data[name] = download_data(ticker, start_date, end_date)

    best_pair = None
    lowest_variance = np.inf
    best_spread = None
    best_series1 = None
    best_series2 = None

    for (name1, serie1), (name2, serie2) in itertools.combinations(data.items(), 2):
        s1 = serie1['Price']
        s2 = serie2['Price']
        common_index = s1.index.intersection(s2.index)
        spread = calculate_spread(s1.loc[common_index], s2.loc[common_index])
        variance = spread.var()

        if variance < lowest_variance:
            lowest_variance = variance
            best_pair = (name1, name2)
            best_spread = spread
            best_series1 = s1.loc[common_index]
            best_series2 = s2.loc[common_index]

    print(f"\nMeilleure paire trouvée : {best_pair[0]} et {best_pair[1]} (variance du spread : {lowest_variance:.6f})")

    best_entry, best_exit, portfolio_value, strategy_returns = optimize_thresholds(best_spread, initial_capital=initial_capital)
    print(f"Seuils optimisés : Entrée = {best_entry:.2f}, Sortie = {best_exit:.2f}")

    plot_pair_trading(best_series1, best_series2, best_spread, portfolio_value, title_suffix=f"{best_pair[0]} vs {best_pair[1]}")

    final_value = portfolio_value.iloc[-1]
    total_return = (final_value - initial_capital) / initial_capital
    sharpe_ratio = calculate_sharpe_ratio(strategy_returns)

    print(f"Performance finale : {final_value:.2f} €")
    print(f"Rendement global de la stratégie : {total_return:.2%}")
    print(f"Sharpe Ratio de la stratégie : {sharpe_ratio:.2f}")

if __name__ == "__main__":
    main()
