# Inventory & Stock Manager

A high-performance, memory-efficient inventory management system built entirely in C. This project utilizes custom data structures (Singly Linked Lists, Queues, and Stacks) to handle dynamic stock tracking, FIFO/LIFO billing pipelines, and automated data persistence without relying on external database engines.

## 🚀 Key Features

* **Dynamic Memory Management:** Utilizes linked lists to allocate memory only when needed, avoiding the rigid constraints of fixed-size arrays.
* **Advanced Sorting:** Implements an $O(n \log n)$ Merge Sort engine using function pointers, allowing the inventory to be dynamically sorted by Price, Quantity, or Expiry Date.
* **Smart Billing (FIFO & LIFO):** 
  * **FIFO (First-In, First-Out):** Uses a custom **Queue** to ensure the oldest stock is sold first.
  * **LIFO (Last-In, First-Out):** Uses a custom **Stack** to sell the most recently added stock first.
* **Automated Analytics:** Scans the inventory to generate aggregated Low Stock and Expiry warnings.
* **File Persistence:** Seamlessly serializes the linked list state to a `inventory_data.csv` file on exit and deserializes it into memory on startup.

## 🛠️ Tech Stack

* **Language:** C
* **Core Concepts:** Pointers, Structs, File I/O, Dynamic Memory Allocation (`malloc`/`free`), Divide and Conquer Algorithms, Abstract Data Types.

## 📂 Project Structure

* `main.c` - Core application loop and user menu interface.
* `inventory_list.h/c` - Linked list foundation, insertion, $O(n)$ searching, and Merge Sort implementation.
* `billing.h/c` - Sale processing, pointer arrays, and empty node deletion.
* `queue.h` & `stack.h` - Inline data structures feeding the billing pipelines.
* `reports.h/c` - Data aggregation for stock and expiry threshold monitoring.
* `storage.h/c` - CSV file serialization and deserialization.
* `date.h` & `node.h` - Core struct definitions and date math helpers.

## 💻 How to Compile and Run

This project requires a standard C compiler (like GCC).

**1. Clone the repository:**
\`\`\`bash
git clone https://github.com/garvdhingra19-pixel/inventory-stock-manager.git
cd inventory-stock-manager
\`\`\`

**2. Compile the source code:**
\`\`\`bash
gcc main.c inventory_list.c reports.c billing.c storage.c -o inventory_manager
\`\`\`

**3. Run the executable:**
* Windows: `.\inventory_manager.exe`
* Linux/Mac: `./inventory_manager`