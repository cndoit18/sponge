FROM ubuntu:bionic

RUN apt-get update \
    && apt-get -y install software-properties-common wget \
    && add-apt-repository multiverse \
    && add-apt-repository universe \
    && add-apt-repository restricted \
    && apt-get update \
    && apt-get -y dist-upgrade

RUN echo "wireshark-common wireshark-common/install-setuid boolean true" | debconf-set-selections      \
    && DEBIAN_FRONTEND=noninteractive apt-get -y install build-essential gdb gcc gcc-8 g++ g++-8 cmake \
        libpcap-dev htop jnettop screen emacs-nox vim-nox automake pkg-config libtool libtool-bin git  \
        tig links parallel iptables mahimahi mininet net-tools tcpdump wireshark telnet socat clang  \
        clang-format clang-tidy coreutils bash doxygen graphviz netcat-openbsd

RUN wget --no-check-certificate -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - \
    && add-apt-repository "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic main" \
    && apt-get update \
    && apt-get -y dist-upgrade \
    && apt-get -y install clangd-9 \
    && update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-9 100

RUN for ver in 7 8; do                                                                      \
        update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-${ver} $((10 * ${ver})) \
            $(for prog in g++ gcc-ar gcc-nm gcc-ranlib gcov gcov-dump gcov-tool; do         \
                echo "--slave /usr/bin/${prog} ${prog} /usr/bin/${prog}-${ver}";             \
            done);                                                                           \
    done

RUN apt-get update \
    && apt-get install -y sudo

RUN adduser --disabled-password --gecos '' docker
RUN adduser docker sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER docker