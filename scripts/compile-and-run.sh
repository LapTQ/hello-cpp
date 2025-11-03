path_src=drafts
# path_src=lessons/01-hello-world
# path_src=lessons/02-setup-build
# path_src=lessons/03-initialization
# path_src=lessons/04-iostream
# path_src=lessons/05-operators
# path_src=lessons/06-functions
# path_src=lessons/07-forward-declaration
# path_src=lessons/08-multiple-code-files
# path_src=lessons/09-namesapces
# path_src=lessons/10-preprocessor
# path_src=lessons/11-header-files
# path_src=lessons/12-header-guards
# path_src=lessons/13-debugging
# path_src=lessons/14-data-types
# path_src=lessons/15-floating-point-numbers
# path_src=lessons/16-boolean-values
# path_src=lessons/17-chars
# path_src=lessons/18-type-conversion
# path_src=lessons/20-literals
# path_src=lessons/21-numeral-systems
# path_src=lessons/23-constexpr-variables
# path_src=lessons/24-std-string
# path_src=lessons/25-std-string_view
# path_src=lessons/26-floating-point-comparisons
# path_src=lessons/27-user-defined-namespaces
# path_src=lessons/28-local-and-global-variables
# path_src=lessons/29-linkage
# path_src=lessons/30-inline-functions-and-variables
# path_src=lessons/31-global-variable-across-files
# path_src=lessons/33-using-declarations-and-using-directives
# path_src=lessons/36-switch-statement
# path_src=lessons/40-pseudo-random-number
# path_src=lessons/42-assert-and-static_assert
# path_src=lessons/44-explicit-type-conversion
# path_src=lessons/46-type-deduction
# path_src=lessons/049-function-templates
# path_src=lessons/050-nontype-template-parameters
# path_src=lessons/052-constexpr-functions
# path_src=lessons/053-consteval
# path_src=lessons/054-constexpr-functions-cont
# path_src=lessons/056-lvalue-references
# path_src=lessons/057-pass-by-lvalue-reference
# path_src=lessons/058-pointers
# path_src=lessons/060-pointers-and-const
# path_src=lessons/061-pass-by-address
# path_src=lessons/062-return-by-reference-and-address
# path_src=lessons/065-user-defined-types
# path_src=lessons/066-unscoped-enumerations
# path_src=lessons/067-scoped-enumerations
# path_src=lessons/068-struct
# path_src=lessons/070-class-template
# path_src=lessons/071-member-functions
# path_src=lessons/072-access-specifiers
# path_src=lessons/074-constructors
# path_src=lessons/075-copy-constructor
# path_src=lessons/076-converting-constructors
# path_src=lessons/080-nested-types
# path_src=lessons/081-destructors
# path_src=lessons/086-std-vector
# path_src=lessons/088-arrays-and-loops
# path_src=lessons/089-for-each
# path_src=lessons/091-std-vector-resizing-and-capacity
# path_src=lessons/092-std-vector-and-stack-behavior
# path_src=lessons/099-pointer-arithmetic-and-subscripting
# path_src=lessons/100-C-style-strings
# path_src=lessons/102-iterators
# path_src=lessons/104-dynamic-memory-allocation
# path_src=lessons/105-void-pointer
# path_src=lessons/106-function-pointer
# path_src=lessons/107-stack-and-heap
# path_src=lessons/108-command-line-arguments
# path_src=lessons/109-ellipsis
# path_src=lessons/110-lambda
# path_src=lessons/111-lambda-captures
# path_src=lessons/112-overload-arithmetic-operators
# path_src=lessons/115-overload-typecast
# path_src=lessons/117-shallow-vs-deep-copy
# path_src=lessons/118-smart-pointers-and-move-semantics
# path_src=lessons/119-rvalue-references
# path_src=lessons/120-move-constructor-and-move-assignment
# path_src=lessons/121-std-unique_ptr
# path_src=lessons/122-std-shared_ptr-and-std-weak_ptr
# path_src=lessons/123-std-initializer_list
# path_src=lessons/124-inheritance
# path_src=lessons/126-overriding
# path_src=lessons/127-hiding-inherited-functionality
# path_src=lessons/128-multiple-inheritance
# path_src=lessons/128-virtual-functions
# path_src=lessons/135-rethrow-exception
# path_src=lessons/139-streams

args_compile=$(cat << EOF
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
# -std=c++17 \
# -Weffc++ \
# -Werror \

args_run=$(cat << EOF
Hello
10
EOF
)

name_out="main.out"

dir_output=outputs
mkdir -p $dir_output

path_out=$dir_output/$name_out
rm -f $path_out

g++ $args_compile -o $path_out $path_src/**.cpp
$path_out $args_run