# ABRnois (Treap) Implementation - Université Gustave Eiffel

This project implements an **ABRnois** (also known as a **Treap**), a data structure that combines properties of Binary Search Trees (BST) and Max-Heaps. It was developed as part of the "Algorithmique des Arbres" (Tree Algorithms) course (L2 Informatique, Semestre 2) at Université Gustave Eiffel.

The primary goal is to process text corpora, efficiently store words and their frequencies, and then extract these words sorted by frequency to generate a word frequency list.

## The ABRnois Data Structure

An ABRnois is a binary tree where each node contains:

1.  **Value (`word`)**: A word (string), ordered according to standard BST rules (lexicographical order). A node's value is greater than all values in its left subtree and less than all values in its right subtree.
2.  **Priority (`nb_occ`)**: The occurrence count of the word, acting as its priority. This follows Max-Heap rules: a node's priority is greater than or equal to the priority of its children.

This hybrid structure allows for both efficient searching/updating based on the word (like a BST) and efficient retrieval of the highest frequency word (like a Max-Heap).

## Features

*   **Corpus Processing**: Reads words sequentially from one or more input text files (`corpus_*.txt`).
*   **ABRnois Construction**: Builds an ABRnois where nodes store unique words and their corresponding frequencies (`nb_occ`).
    *   If a word is encountered for the first time, a new node is added with `nb_occ = 1`.
    *   If an existing word is encountered, its `nb_occ` is incremented.
*   **Insertion (`insert_ABRnois`)**: Implements insertion that maintains both BST (lexicographical) and Max-Heap (frequency) properties. This involves standard BST insertion followed by rotations *upwards* to restore the heap property if necessary.
*   **Max Priority Extraction (`extrait_priorite_max`)**: Retrieves and removes *all* nodes with the current maximum frequency (the root's frequency).
    *   Uses rotations *downwards* to move the max-priority node(s) towards the leaves before removal.
    *   Handles ties: if multiple words share the maximum frequency, all are extracted in one call.
    *   The extracted nodes are returned in a list, sorted alphabetically.
*   **Frequency List Generation**: Creates an output file (`<output_freq_file>`) listing words sorted primarily by frequency (descending) and secondarily by alphabetical order, along with their percentage frequency.
*   **Visualization (Optional `-g`)**: Can generate graphical representations of the ABRnois state (as PDF files using Graphviz) after each insertion and extraction step. Files are named `insertion_1.pdf`, `insertion_2.pdf`, ..., `suppression_1.pdf`, `suppression_2.pdf`, ...
*   **Top-N Output (Optional `-n p`)**: Limits the output frequency list to the top `p` most frequent words. If there are ties in frequency at the p-th position, all tied words are included.

## Core Algorithms

### Insertion

1.  Perform a standard BST insertion based on the word (`mot`).
2.  If the word already exists, simply increment its `nb_occ`.
3.  After insertion or incrementing `nb_occ`, traverse back up the path from the affected node to the root.
4.  At each step, if the current node's priority (`nb_occ`) is less than its child's priority, perform the appropriate rotation (left or right) to restore the Max-Heap property.

### Max Priority Extraction

1.  Identify the maximum priority `p_max`, which is the priority of the root node.
2.  While the root node has priority `p_max`:
    a.  Store the root node temporarily.
    b.  Perform rotations downwards to move this node towards a leaf position.
        *   If the node has two children, compare their priorities. Rotate the child with the higher priority upwards. If priorities are equal, prefer a left rotation (rotating the right child up).
        *   If the node has only one child, perform the only possible rotation.
    c.  Continue rotating the target node downwards until it becomes effectively disconnected or a leaf.
    d.  Add the disconnected node to a temporary list.
3.  After extracting all nodes with `p_max`, sort the temporary list alphabetically by word.
4.  Return the sorted list and the count of extracted nodes.

## Dependencies

*   A C compiler (e.g., `gcc`)
*   **(Optional)** `make` for easier compilation
*   **Graphviz**: The `dot` command must be installed and in the system's PATH to use the `-g` visualization feature.

## Compilation

Compile the C source file using a C compiler like `gcc`:

```bash
gcc abrnois.c -o abrnois -lm
```

or use `make` if you have a `Makefile`:

```bash
make lancer
```

## Usage

Run the program with the following command:

```bash
./abrnois <output_freq_file> <corpus1.txt> [corpus2.txt ...] [-g] [-n p]
```

Where:
*   `<output_freq_file>`: The name of the output file for the frequency list (e.g., `frequents.txt`).
*   `<corpus1.txt>`: The first input text file containing words to process.
*   `[corpus2.txt ...]`: Additional input text files (optional).
*   `-g`: Optional flag to generate graphical representations of the ABRnois state after each insertion and extraction step.
*   `-n p`: Optional flag to limit the output to the top `p` most frequent words. If there are ties at the p-th position, all tied words will be included.

Example:

```bash
./abrnois word_stats.txt book1.txt book2.txt -n 1500 -g
```

This command will process `book1.txt` and `book2.txt`, generate a frequency list in `word_stats.txt`, limit the output to the top 1500 most frequent words, and create graphical representations of the ABRnois state after each insertion and extraction step.

## Project Context

This code was developed for the DM2 (Homework 2) assignment of the "Algorithmique des Arbres" course (L2 Informatique, S2, 2024-2025) at Université Gustave Eiffel. The project aims to enhance understanding of tree algorithms and their applications in data structures.