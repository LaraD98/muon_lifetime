FROM debian:bullseye

RUN apt update && apt install -y clang make cmake qtbase5-dev libconfig++-dev wget libexpat1-dev git

RUN mkdir -p /builddir/muon_lifetime/build && cd /builddir/muon_lifetime && git clone https://github.com/dtreffenstaedt/muon_lifetime.git

RUN mkdir -p /builddir/geant4/build && cd /builddir/geant4 && git clone https://github.com/Geant4/geant4.git && cd geant4 && git checkout v10.6.1

RUN cd /builddir/geant4/build && cmake -DGEANT4_USE_QT=OFF -DGEANT4_USE_OPENGL_X11=OFF ../geant4 && cmake -DGEANT4_INSTALL_DATA=ON . && make -j6 && make install

RUN cd /builddir/muon_lifetime/build && cmake ../muon_lifetime/source && make -j6

ENTRYPOINT ["/bin/bash"]
