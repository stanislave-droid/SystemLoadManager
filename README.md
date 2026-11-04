# SystemLoadManager
## Desciption
> Project works only on the Windows platform!
<p>That`s an application written in C++ to get information on system status.</p>
<p>It delivers its owner some useful information about CPU, memory and disks.</p>
<p>You can get: CPU and memory load + free memory - these values update every 300 ms;
   CPU cores, threads and base speed; total memory in MB.
   For disks: the program scans your computer for available drives and gets their name, free, used and total space.</p>
<p>All that information is written in the console in a table view, and some of this info shows certain colors depending on its state.</p>
<p>For smooth re-rendering of values, a console handler was used.</p>
<p>There is also one bug/feature that I didn`t want to fix just because it looks cool. Sometimes, CPU load goes beyond 100% and can even show inf% if your CPU load is insane.</p>

### Tech Stack

| Category             | Technology                   |
| -------------------- | ---------------------------- |
| Languages            | C++                          |
| Tools and utils      | Visual Studio, Git, GitHub   |
| Libraries            | Tabulate for table view      |
| Others               | WinApi, thread, memory       |

### Project Architecture:
```
/
├──CPU_M         # CPU monitor class, gets info about CPU 
├──Memory_M      # Memory monitor class, gets info about ram usage
├──Disk_M        # Disk monitor class, gets info about disk fulfield
├──main          # Main startup file
├──tabulate      # Open source library for tables in the console
```

### Delivered Info

| Category             | Info                                       |
| -------------------- | ------------------------------------------ |
| CPU                  | CPU load, Cores, Threads, Base speed       |
| Memory               | Memory Load, Free, Total                   |
| Disk                 | Each disk name, Free space, Used and Total |

### Developers
- [Drochak Stanislav](https://www.linkedin.com/in/stanislav-drochak/)

<h1>Show case:</h1>

### Main view:
<img width="566" height="396" alt="image" src="https://github.com/user-attachments/assets/b318266f-a7bf-40db-9a61-3d5a202998c6" />

### Colors State depending on load
| State in % | Color              |
| ---------- | ------------------ |
|   0 - 30   | ![green](https://github.com/user-attachments/assets/dd52fedb-4365-47f0-a904-aa4757c64271) |
|   30 - 70  | ![yellow](https://github.com/user-attachments/assets/6b13322e-431b-4165-8a0b-ecfb441fcf93) |
|   70 - 100 | ![red](https://github.com/user-attachments/assets/807cccb7-e770-4343-946e-08af4a123c48) |
