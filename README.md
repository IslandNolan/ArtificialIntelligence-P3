# Knowledge Based Intelligence System
##### Project 3 by: Francisco, Nolan, Daniel

## Build Instructions: 

### Dependencies (Linux Fedora):

    - cmake           (v3.21+)
    - glib            (~)
    - glib-devel      (~)
    - glibmm2.4       (~)
    - gtkmm30         (~)
    - gtkmm30-devel   (~)
    - gtk3            (v3+)  
    - ninja-build     (v1.10+)
    
    Packages are present in the Fedora 36 repositories.
    The Naming Comvention will vary based on distribution.


### Build
#### (Build Instructions are not available on MacOS, or Windows)

1. Clone this Project
2. Install the listed dependencies
    Fedora 36
    ```
    sudo dnf install --assumeyes \
            cmake gtkmm30-devel gtkmm30 gtk3 \
            ninja-build glib \
            glib-devel \
            glibmm2.4 
    ```
3. Generate Build files for C-Make: 
    ```
    cmake -S=. -B=build/ -G=Ninja
    ```

4. Launch ```compile.sh``` to build the program. The executable will be moved to the Project root if successful.







