FROM fedora:36

#Setup build environment
RUN dnf update --refresh --assumeyes

RUN dnf install cmake gtkmm30-devel gtkmm30 gtk3 \
                ninja-build glib \
                glib-devel \
                glibmm2.4 --assumeyes

#Copy files to image

#Coming Soon ;)


#Execute Build Process


#Finished

