path_src=lessons/01-hello-world
path_src=lessons/02-setup-build
path_src=lessons/03-initialization
path_src=lessons/04-iostream
path_src=lessons/06-functions
path_src=lessons/07-forward-declaration
path_src=lessons/08-multiple-code-files
path_src=lessons/09-namesapces

args=$(cat << EOF
-fdiagnostics-color=always \
-g \
-ggdb \
-O2 \
-DNDEBUG \
-pedantic-errors \
-Wall \
-Weffc++ \
-Wextra \
-Wconversion \
-Wsign-conversion \
-Werror \
-std=c++17
EOF
)

name_out="main.out"

dir_output=outputs
mkdir -p $dir_output

path_out=$dir_output/$name_out

g++ $args -o $path_out $path_src/**.cpp
$path_out