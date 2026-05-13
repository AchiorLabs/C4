#!/usr/bin/env bash

set -e

OUTPUT_BINARY="app"
SOURCE_FILE="src/main.c4"

show_help()
{
    echo "C4 Project Manager"
    echo
    echo "Usage:"
    echo "  c4pm new <project_name>     Create a new application project"
    echo "  c4pm lib <project_name>     Create a new library project"
    echo "  c4pm build                  Build current project"
    echo "  c4pm run                    Build and run current project"
    echo
}

create_project()
{
    local name="$1"

    if [ -z "$name" ];
    then
        echo "error: project name expected"
        exit 1
    fi

    mkdir -p "$name/src"

    cat > "$name/src/main.c4" <<EOF
fn main() -> i32:
    return 0
:
EOF

    echo "created application project: $name"
}

create_library()
{
    local name="$1"

    if [ -z "$name" ];
    then
        echo "error: library name expected"
        exit 1
    fi

    mkdir -p "$name/lib"
    mkdir -p "$name/src"

    cat > "$name/src/lib.c4" <<EOF
fn hello() -> void:
    return
:
EOF

    echo "created library project: $name"
}

build_project()
{
    if [ ! -f "$SOURCE_FILE" ];
    then
        echo "error: $SOURCE_FILE not found"
        exit 1
    fi

    echo "building project..."

    C4C \
        -i "$SOURCE_FILE" \
        -o "$OUTPUT_BINARY" \
        -t x86_64-linux-gnuC \
        --emit-c

    make
    make clean

    echo "build complete"
}

run_project()
{
    build_project

    if [ ! -f "./$OUTPUT_BINARY" ];
    then
        echo "error: binary '$OUTPUT_BINARY' not found"
        exit 1
    fi

    echo "running $OUTPUT_BINARY..."
    "./$OUTPUT_BINARY"
}

if [ $# -eq 0 ];
then
    show_help
    exit 1
fi

case "$1" in
    new)
        create_project "$2"
        ;;

    lib)
        create_library "$2"
        ;;

    build)
        build_project
        ;;

    run)
        run_project
        ;;

    *)
        echo "error: unknown command '$1'"
        echo
        show_help
        exit 1
        ;;
esac