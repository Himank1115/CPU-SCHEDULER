# CPU Scheduler Algorithm

## Project Description

This project implements a CPU Scheduler algorithm using a C++ core for the algorithm implementation, with a PHP backend server and an HTML frontend. The goal of this project is to simulate and visualize various CPU scheduling algorithms, providing users with an interactive and educational tool to understand how different scheduling techniques work.

### Key Features

- **Algorithm Implementation:** The core scheduling algorithms are implemented in C++ for efficient computation.
- **Web-Based Interface:** A user-friendly web interface created with PHP and HTML allows users to interact with the scheduler, input data, and view results.
- **Algorithm Options:** The project supports multiple scheduling algorithms such as First-Come, First-Served (FCFS), Shortest Job Next (SJN), Priority Scheduling, Round Robin (RR), and more.
- **Visualization:** The interface includes graphical representations of scheduling processes to help users visualize how tasks are managed and executed by the CPU.

### Technologies Used

- **Algorithm Core:** C++ for implementing the CPU scheduling algorithms.
- **Backend Server:** PHP for handling server-side logic and communication between the frontend and the algorithm core.
- **Frontend:** HTML for the client-side interface.

### How to Run

1. **Setup Algorithm Core:**
   - Ensure you have a C++ compiler installed.
   - Compile the C++ source files using the following command:
     ```sh
     g++ -o scheduler scheduler.cpp
     ```

2. **Setup Backend Server:**
   - Make sure you have a web server with PHP support (e.g., Apache, Nginx).
   - Place the PHP files in the web server's root directory.
   - Ensure the compiled C++ executable (`scheduler`) is accessible from the PHP scripts.

3. **Setup Frontend:**
   - Place the HTML files in the web server's root directory.

4. **Run the Project:**
   - Start the web server.
   - Open a web browser and navigate to `http://localhost` (or the relevant URL where your server is hosted).
   - Use the web interface to input process details and select the desired scheduling algorithm.
   - View the scheduling results and visualizations.

### Usage

- Enter the details of the processes including their burst times, arrival times, and priorities (if applicable).
- Select the scheduling algorithm you want to simulate.
- Click on the "Run" button to execute the scheduling algorithm.
- View the scheduling order and other relevant statistics such as turnaround time and waiting time.

### Internal Working

The project is divided into three main parts: the algorithm core, the backend server, and the frontend.

#### Algorithm Core (C++)

1. **Input Handling:** The C++ core receives process details (burst time, arrival time, priority, etc.) from the backend server.
2. **Algorithm Execution:** Based on the selected scheduling algorithm, the core processes the input using one of the implemented algorithms:
   - **FCFS (First-Come, First-Served):** Processes are scheduled in the order they arrive.
   - **SJN (Shortest Job Next):** Processes are scheduled based on the shortest burst time.
   - **Priority Scheduling:** Processes are scheduled based on priority levels.
   - **Round Robin:** Processes are scheduled in a cyclic order with a fixed time quantum.
3. **Result Calculation:** The core calculates various metrics like waiting time, turnaround time, and completion time for each process.
4. **Data Transmission:** The results are sent back to the backend server for further handling.

#### Backend Server (PHP)

1. **Server-Side Logic:** PHP handles form submissions from the frontend, sends the data to the C++ core, and retrieves the results.
2. **Data Processing:** PHP processes the data received from the C++ core and prepares it for visualization.
3. **Communication:** Ensures smooth communication between the frontend and the algorithm core.

#### Frontend (HTML)

1. **User Interface:** The HTML frontend provides a form for users to input process details and select the scheduling algorithm.
2. **Result Display:** The results from the backend server are displayed on the web page, including graphical representations of the process scheduling order and other relevant statistics.

### Learning Takeaways

- **Understanding Scheduling Algorithms:** Gained in-depth knowledge of various CPU scheduling algorithms and their real-world applications.
- **Backend Development:** Enhanced PHP programming skills, particularly in handling server-side logic and data communication.
- **Algorithm Development:** Improved C++ programming skills, especially in implementing complex algorithms and data structures.
- **Frontend Development:** Learned to create dynamic and interactive web interfaces using HTML.
- **Integration:** Developed skills in integrating different technologies (C++ algorithm core with PHP backend and HTML frontend) to build a cohesive project.
- **Problem-Solving:** Developed problem-solving skills by addressing challenges related to algorithm implementation, data handling, and communication between different components.
- **Visualization:** Gained experience in presenting data visually to enhance user understanding and engagement.

### Resources

- [CPU Scheduling Basics - YouTube Playlist](https://www.youtube.com/playlist?list=PLBlnK6fEyqRitWSE_AyyySWfhRgyA-rHk) - For understanding the basic concepts of CPU scheduling.
- Chapter 4 of *Linux Kernel Development* by Robert Love - For detailed implementation insights and advanced topics.

### Contributions

Contributions are welcome! If you find any bugs or have suggestions for improvements, please create an issue or submit a pull request.


