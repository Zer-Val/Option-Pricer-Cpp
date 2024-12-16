#pragma once
#include <vector>
#include <iostream>
#include <iomanip>  // For setw

template <typename T>
class BinaryTree {
public:
    BinaryTree() : _depth(0) {}

    void setDepth(int depth);
    void setNode(int level, int index, T value);
    T getNode(int level, int index) const;
    void display() const;

private:
    int _depth;
    std::vector<std::vector<T>> _tree;
};

template <typename T>
void BinaryTree<T>::setDepth(int depth) {
    _depth = depth; // Ajouter 1 pour que la profondeur de 3 signifie 4 étages
    _tree.resize(_depth + 1);
    for (int i = 0; i <= _depth; ++i) {
        _tree[i].resize(i + 1);
    }
}

template <typename T>
void BinaryTree<T>::setNode(int level, int index, T value) {
    if (level <= _depth && index <= level) {
        _tree[level][index] = value;
    }
}

template <typename T>
T BinaryTree<T>::getNode(int level, int index) const {
    if (level <= _depth && index <= level) {
        return _tree[level][index];
    }
    throw std::out_of_range("Invalid indices");
}

template <typename T>
void BinaryTree<T>::display() const {

    if (_depth == 0) return;
    else {

        for (int i = 0; i <= _depth && i < _tree.size(); ++i) {
            for (int j = 0; j <= i && j < _tree[i].size(); ++j) {
                std::cout << _tree[i][j] << " ";
            }
            std::cout << std::endl;
        }
        for (int e = 0; e < 2; e++) {
            std::cout << std::endl;
        }
        for (int i = 0; i <= _depth; ++i) {
            // Calculer les espaces avant le premier nombre
            int leadingSpaces = 3 * (_depth - i);

            // Imprimer les espaces avant le premier nombre
            for (int space = 0; space < leadingSpaces; ++space) {
                std::cout << " ";
            }
            // Imprimer les valeurs pour le niveau actuel
            for (int j = 0; j <= i; ++j) {
                std::cout << std::setw(2) << _tree[i][j]; // Imprimer chaque valeur avec une largeur fixe de 2 caractères
                if (j < i) {
                    for (int space = 0; space < 3; ++space) {
                        std::cout << " "; // Espaces entre les valeurs
                    }
                    if (_tree[i][j] < 99 && std::floor(_tree[i][j]) == _tree[i][j]) {
                        std::cout << " "; // Espaces supplémentaires pour les nombres à 3 chiffres
                    }
                }
            }
            std::cout << std::endl;

            // Imprimer les barres obliques pour chaque niveau, sauf le dernier
            if (i < _depth) {
                int slashLeadingSpaces = 3 * (_depth - i) - 1;

                // Imprimer les espaces avant le premier /
                for (int space = 0; space < slashLeadingSpaces; ++space) {
                    std::cout << " ";
                }

                for (int j = 0; j <= i; ++j) {
                    std::cout << "/";
                    for (int space = 0; space < 3; ++space) {
                        std::cout << " "; // Espaces entre / et \ //
                    }
                    std::cout << "\\";
                    if (j < i) {
                        for (int space = 0; space < 1; ++space) {
                            std::cout << " "; // Espaces entre chaque paire de / et \ //
                        }
                    }
                }
                std::cout << std::endl;
            }
        }

        std::cout << std::endl;
    }
}

