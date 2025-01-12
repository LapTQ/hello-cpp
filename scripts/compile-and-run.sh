path_src=lessons/1-hello-world
path_src=lessons/2-setup-build
path_src=lessons/3-initialization
path_src=lessons/4-iostream
path_src=lessons/6-functions
path_src=lessons/7-forward-declaration
path_src=lessons/8-multiple-code-files
path_src=lessons/9-namesapces

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