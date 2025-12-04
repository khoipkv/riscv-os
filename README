## RISC-V Simple Operating System (OS)

This project is a **minimal operating system** being developed as a **self-learning exercise**. It is primarily based on the concepts and structure presented in the book [Operating System in 1,000 Lines](https://1000os.seiya.me/en/)

---

### Core Features (From the Book)

The core development of this OS focuses on implementing the following fundamental concepts as outlined by the guiding book:

* **Multitasking:** Implement the ability to **switch between processes** to allow multiple applications to share the CPU time efficiently (basic scheduling).
* **Exception Handler:** Create robust routines to handle events requiring OS intervention, such as illegal instructions, alignment errors, and other **synchronous exceptions**.
* **Paging:** Implement support for the RISC-V **MMU** (Memory Management Unit) to provide an **isolated memory address space** for each application, enhancing security and stability.
* **System Calls:** Define and implement a set of interfaces that allow user applications to **call kernel features** (e.g., I/O operations, process creation).
* **Device Drivers:** Create abstract software layers to manage and control essential **hardware functionalities**, such as console output and disk read/write operations.
* **File System:** Implement a basic structure to **manage files on disk** or in memory.
* **Command-line Shell:** Provide a simple **user interface** for humans to interact with the OS.

---

### RISC-V Architecture

This OS is specifically targeting the **RISC-V Instruction Set Architecture (ISA)**, which is an open-standard, free, and extensible ISA.

* The current implementation is designed for the **RV32I** variant.
* Key elements utilized include the **Machine Mode (M-mode)** for initial booting and the transition to **Supervisor Mode (S-mode)** for the kernel's main execution.

---

### Future Features (Roadmap)

Once the core features above are stable, the plan is to gradually expand the OS's capabilities with these more advanced elements:

* **Interrupt Handlers:** Implementing robust mechanisms to handle **asynchronous events** from external hardware and the RISC-V **PLIC** (Platform-Level Interrupt Controller).
* **Timer Processing:** Setting up the RISC-V **CLINT** (Core Local Interruptor) or equivalent to generate periodic interrupts for **scheduling** and **time-keeping**.
* **Inter-Process Communication (IPC):** Developing mechanisms (e.g., messages, shared memory) to allow **independent processes to exchange data** and coordinate execution.
* **Multi-Processor Support (SMP):** Adapting the kernel to run safely and efficiently across **multiple CPU cores** by addressing synchronization and cache coherency.
