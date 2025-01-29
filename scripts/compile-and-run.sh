path_src=lessons/01-hello-world
path_src=lessons/02-setup-build
path_src=lessons/03-initialization
path_src=lessons/04-iostream
path_src=lessons/05-operators
path_src=lessons/06-functions
path_src=lessons/07-forward-declaration
path_src=lessons/08-multiple-code-files
path_src=lessons/09-namesapces
path_src=lessons/10-preprocessor
path_src=lessons/11-header-files
path_src=lessons/12-header-guards
path_src=lessons/13-debugging
path_src=lessons/14-data-types
path_src=lessons/15-floating-point-numbers
path_src=lessons/16-boolean-values
path_src=lessons/17-chars
path_src=lessons/18-type-conversion
path_src=lessons/20-literals
path_src=lessons/21-numeral-systems
path_src=lessons/23-constexpr-variables
path_src=lessons/24-std-string
path_src=lessons/25-std-string_view
path_src=lessons/26-floating-point-comparisons
path_src=lessons/27-user-defined-namespaces
path_src=lessons/28-local-and-global-variables
path_src=lessons/29-linkage
path_src=lessons/30-inline-functions-and-variables
path_src=lessons/31-global-variable-across-files
path_src=lessons/33-using-declarations-and-using-directives
path_src=lessons/36-switch-statement
path_src=lessons/40-pseudo-random-number
path_src=lessons/42-assert-and-static_assert
path_src=lessons/44-explicit-type-conversion
path_src=lessons/46-type-deduction
path_src=lessons/049-function-templates
path_src=lessons/050-nontype-template-parameters
path_src=lessons/052-constexpr-functions

args=$(cat << EOF
-fdiagnostics-color=always \
-g \
-ggdb \
-O2 \
-DNDEBUG \
-pedantic-errors \
-Wall \
-Wextra \
-Wconversion \
-Wsign-conversion \
-std=c++17 \
-I./lessons/11-header-files/others \
-I./3rd-parties/plog/include
EOF
)
# -Weffc++ \
# -Werror \

name_out="main.out"

dir_output=outputs
mkdir -p $dir_output

path_out=$dir_output/$name_out
rm -f $path_out

g++ $args -o $path_out $path_src/**.cpp
$path_out