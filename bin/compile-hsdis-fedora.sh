#!/bin/bash
set -euo pipefail

TARGET=$(mktemp --directory /var/tmp/hsdis.XXXXXXXXXX)

(
    cd "${TARGET}"

    dnf download --source binutils java-1.8.0-openjdk
    aunpack java-1.8.0-openjdk-*.src.rpm
    aunpack binutils-*.src.rpm

    (
        cd java-1.8.0-openjdk-*.src
        aunpack aarch64-port-jdk8u-*.tar.xz

        (
            cd openjdk/hotspot/src/share/tools/hsdis
            mkdir build

            (
                cd build
                aunpack "${TARGET}"/binutils-*.src/binutils-*.tar.xz
                mv binutils-* binutils
            )

            make ARCH=amd64
        )
    )
)

mv "${TARGET}"/java-1.8.0-openjdk-*.src/openjdk/hotspot/src/share/tools/hsdis/build/linux-amd64/hsdis-amd64.so .
rm -rf "${TARGET}"
