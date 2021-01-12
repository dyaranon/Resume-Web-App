FROM gcc:7.3.0

RUN apt-get -qq update
RUN apt-get -qq upgrade
RUN apt-get -qq install cmake
RUN apt-get -qq install build-essential libtcmalloc-minimal4 && \
    ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so

RUN apt update \
	&& apt install -y \
		build-essential \
		libboost-all-dev 