FROM fedora:36

#Setup Env
RUN dnf update --refresh --assumeyes
RUN dnf groupinstall 'Development Tools' --assumeyes
RUN dnf install cmake gtkmm30-devel gtkmm30 gtk3 \
                ninja-build glib \
                glib-devel \
                glibmm24 g++ --assumeyes

#Copy files to image
COPY src/sources/ build/src/sources/
COPY include/ build/include/
COPY inputs/ build/inputs/
COPY CMakeLists.txt build/CMakeLists.txt
COPY compile.sh build/compile.sh


#Execute Build Process
WORKDIR /build/
RUN cmake -S=. -B=build/ -G=Ninja
RUN ./compile.sh


#This doesn't quite work. Application Builds, but cannot forward wayland to GTK-Broadway
#In leighman's terms, cannot see the application window, but it launhes.
CMD ./ArtificialIntelligenceP3 --env="$DISPLAY"