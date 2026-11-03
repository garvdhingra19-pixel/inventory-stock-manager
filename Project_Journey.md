Project_Journey.md - Phase 1: Foundation

Goal Accomplished: Established the fundamental C data structures (Date, Node, InventoryList) and a menu-driven interface to add and view inventory batches dynamically in memory.

Core Concept: Structs, Pointers, and Singly Linked Lists.

The Analogy (The Freight Train): Think of your inventory system as a freight train.

Structs (Node, Date): The physical blueprints defining how to build a train car and how to pack the cargo (product ID, price, expiry date) inside it.

The List (InventoryList): The station master keeping track of the train. The head pointer watches the locomotive (the first car), and the tail pointer watches the caboose (the last car).

The Pointers (next): The heavy steel couplings connecting one train car to the one immediately behind it.

Adding a Batch: When you use insertAtTail, you are building a new train car, rolling it up to the caboose, locking the coupling, and telling the station master that this new car is the new caboose.

Because you only have forward-facing couplings (next), you can only walk from the front of the train to the back. This linear structure dictates how we will build our search algorithm next.

Phase 2: Search and Linear Scanning

Goal Accomplished: Added the ability to query the inventory by ID or Name using case-insensitive partial matching.

Core Concept: Linear Traversal and O(n) Time Complexity.

The Analogy (The Train Inspector): Because a linked list is like a freight train, you cannot instantly teleport to the exact car containing the product you want (like you could with an array index or a hash map). To find a specific item, the Train Inspector must start at the locomotive (head) and walk through the train car by car (current = current->next), reading every single shipping manifest along the way. If the train has n cars, the worst-case scenario requires the inspector to check n cars. This makes the search operation O(n) in time complexity.

Phase 3: Sorting via Merge Sort

Goal Accomplished: Organized the inventory by Price, Quantity, or Expiry using an O(n log n) Merge Sort, powered by function pointers for dynamic rules.

Core Concept: Divide and Conquer, Pointer Manipulation, Function Pointers.

The Analogy (The Train Yard Shunting): Imagine sorting our freight train cars by weight. Instead of unhooking and re-hooking one car at a time (Bubble Sort), we split the entire train in half, split those halves in half, and so on until every car is separated. Then, we take two cars, compare their weights, hook them together in order, and repeat the process, zipping small sorted trains into larger sorted trains. We also hired an inspector who follows dynamic rules (Function Pointers)—we just hand him a clipboard saying "Check Weight" or "Check Expiry Date," and the exact same sorting machinery works flawlessly without needing to be rebuilt.

Phase 4: Inventory Reports (Data Aggregation)

Goal Accomplished: Created dynamic reports that aggregate data across the linked list. The low-stock report sums quantities across multiple batches of the same product, and the expiry report calculates date differences to flag perishables.

Core Concept: Data Aggregation, Sub-queries, and Date Math.

The Analogy (The Auditor): To find low stock, the Train Inspector cannot just look at one car. Product #101 might have 3 items in car 2, and 8 items in car 5. The Inspector (our code) walks the entire train, keeping a scratchpad (the checkedIds array) to remember which products they've already tallied. For each new product they discover, they send a secondary auditor (scanner) down the rest of the train to sum up the total count.

Phase 5: Automated Billing (FIFO/LIFO)

Goal Accomplished: Implemented complex sale logic utilizing Queue and Stack data structures to calculate itemized bills based on arrival dates, skipping expired goods, and safely removing empty nodes from the main list.

Core Concept: Queues (FIFO), Stacks (LIFO), Pointer Arrays, and Node Deletion.

The Analogy (The Warehouse Foreman): When a customer orders 50 baskets, the Foreman checks the manifest, builds an array of all train cars holding baskets, and ignores the ones with spoiled goods. If the company policy is FIFO, he builds a Queue (a one-way tunnel) where the oldest cars enter first. If policy is LIFO, he builds a Stack (a dead-end tunnel) where the newest cars enter last and leave first. He unpacks the requested amount, charges the specific price from that car, and if a car becomes totally empty, he unhooks it from the train and sends it to the scrap yard (free()).

Phase 6: File Persistence (CSV Storage)

Goal Accomplished: Bridged volatile memory (RAM) with non-volatile storage (Disk) by translating the linked list into a comma-separated values (CSV) file on exit, and parsing it back into memory on launch.

Core Concept: File I/O (fopen, fprintf, fscanf), Data Serialization.

The Analogy (The Ledger Book): At the end of the day, the Station Master cannot just go home, or they will forget where all the trains are (RAM clears when the program closes). Before clocking out, they walk the train and write down every car's stats in a permanent physical ledger book (fprintf to .csv). The next morning, before letting anyone use the terminal, they read the book line-by-line (fscanf) and rebuild the exact train yard in memory.

Phase 7: System Complexity & Final Documentation

Goal Accomplished: Documented the time complexity of all major operations to prove the system's efficiency and theoretical correctness.

Core Concept: Algorithmic Time Complexity (Big-O Notation).

The Analogy (The Architect's Blueprint): An architect doesn't just build a train station; they mathematically prove it can handle rush hour. Big-O notation is our blueprint. It tells us how the system slows down as our inventory grows from 10 items to 10,000 items. Because we kept a pointer at the very back of the train (tail), adding new cars takes the exact same amount of time no matter how long the train gets (O(1)). Sorting the train uses a divide-and-conquer strategy (O(n log n)), which is exponentially faster than comparing every car to every other car.

Time Complexity Summary:Insert at tail: O(1) (Direct pointer access via tail).Search by ID/Name: O(n) (Linear scan of $n$ nodes).Merge Sort: O(n log n) (Logarithmic split, linear merge).Expiry Report: O(n) (Linear traversal).Low Stock Report: O(n * k) (Nested scan where $k$ is unique products).Process Sale (Billing): O(n + m log m) (Scans $n$ nodes, sorts $m$ matching batches).Queue & Stack Operations: O(1) (Direct head/tail pointer manipulation).