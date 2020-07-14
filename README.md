# System Monitor
This system monitor shows:
- Hostname
- Username
- Uptime
- CPU model
- CPU frequency(MHz)
- RAM amount
- The amount of RAM used without cached data

### Installation
GTK3 is installed by default, please don't download and compile from the GTK website.To use gtk3 apps you don't need to install anything. But, if you want to develop (or even just compile) apps this is what you're looking for:
```
    sudo apt-get install libgtk-3-dev
```

### Example of use
As a result, we should get such a system monitor:

|     hostname     |                    vm                    |
|------------------|:----------------------------------------:|
|    username      |                   root                   |
|     Uptime       |              0.h 59 m. 20 s.             |
|    CPU model     | Intel(R) Core(TM) i5-7200U CPU @ 2.50GHz |
|     CPU MHz      |                 2712.006                 |
|   Mem Available  |             1Gb 324 Mb 112 Kb            | 
|     Mem Active   |               661 Mb 920Kb               |

### License
This project is made available under the MIT License.

