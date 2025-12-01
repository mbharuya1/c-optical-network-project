# Optical Fiber Network Reconstruction Project – C Data Structures & Algorithms

This project focuses on the **reconstruction, representation, and management of an optical fiber network**.  
A network is modeled as a set of cables, each containing fiber bundles connecting different clients.  
The project uses several data‑structure approaches: **linked lists, hash tables, quadtree spatial indexing, and graphs**.

It was developed as part of a systems & algorithms course at **Sorbonne Université**.

---

## Project Overview

This project aims to manipulate and reorganize a complex fiber‑optic network using multiple C data structures:

### ✔️ Core objectives
- Parse and represent chains of points from input files  
- Reconstruct a network using:
  - **Linked lists**
  - **Hash tables**
  - **Quadtree structures**
- Generate and visualize the network (SVG + graph structures)
- Build and analyze the client connectivity graph  
- Compare performance across data-structure implementations

Each module corresponds to one exercise of the original assignment.

---

## Project Structure

### **Exercice 1 — Reading & Writing Chains**
Files:  
- `Chaine.c`  
- `Chaine.h`

Contains all functions to:
- Read `.cha` chain files  
- Store points in linked lists  
- Display or export chains to output files  

---

### **Exercices 2 & 3 — Network Reconstruction (List-based Implementation)**
Files:  
- `Reseau.c`  
- `Reseau.h`  
- `ReconstitueReseau.c` (main for question 2.3)

Implements:
- Creation of nodes  
- Representation of neighbors  
- Construction of the whole network using linked lists  
- Counting links and commodities  
- Generating SVG visualization (`afficheReseauSVG`)  
- Exporting reconstructed networks to `.txt` files  

---

### **Exercice 4 — Hash Table Implementation**
Files:  
- `Hachagee.c`  
- `Hachage.h`

Implements:
- Hashing of (x, y) coordinates  
- Faster lookup for nodes than linked lists  
- Performance analysis  

---

### **Exercice 5 — Quadtree Representation**
Files:  
- `ArbreQuat.c`  
- `ArbreQuat.h`

Implements:
- Spatial indexing for efficient search  
- Insertion of nodes in a quadtree  
- Network reconstruction using 2D partitioning  

---

### **Exercice 6 — Main Programs**
Files:  
- `main.c` (main of question 1)  
- `graph.c` (main of question 3)

Implements:
- Reconstruction timing  
- Comparison between list, hash table, and quadtree building times  
- Export of timing results  

---

### **Exercice 7 — Graph Construction**
Files:  
- `Graphe.c`  
- `Graphe.h`

Implements:
- Conversion of the optical network into a graph  
- Each node = client  
- Edges = fiber links  
- Used for connectivity analysis  

---

## Additional Files

### **Utility & Provided Files**
- `Struct_File.h` & `Struct_File.c`  
  → Provided queue implementation used in Exercise 7  
- `SVGwriter.h`  
  → Generates SVG/HTML visualizations of networks  
- `liste_script.gnuplot`  
  → Script used to generate performance plots  
---

## Compile & Run

To compile everything:
```bash
make
```

To run reconstruction programs:
```bash
./reconstitue
./main
./graph
```

To visualize networks:
- Output SVG/HTML files are created automatically (via `SVGwriter`)

To generate performance graphs:
```bash
gnuplot liste_script.gnuplot
```

---

(clean, professional, consistent with your previous repos)

