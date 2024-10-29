path_src=lessons/1-hello-world/main.cpp
path_src=lessons/2-setup-build/getLanguageStandard.cpp
path_src=lessons/3-initialization/main.cpp
path_src=lessons/4-iostream/main.cpp

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

name_out="${path_src//\//--}"
name_out="${name_out%%.cpp}".out

dir_output=outputs
mkdir -p $dir_output

path_out=$dir_output/$name_out

g++ $args -o $path_out $path_src
$path_out