

## Cơ chế hoạt động của `std::cin >>` (Tóm tắt đơn giản)

1. Bước đầu tiên, `std::cin >>` sẽ tự động bỏ qua tất cả các ký tự khoảng trắng (*whitespace*) nằm ở đầu *input buffer*.
2. Lúc này, nếu *input buffer* trống, toán tử `>>` sẽ dừng lại chờ người dùng nhập dữ liệu. Sau khi người dùng nhập xong, các *whitespace* ở đầu lại tiếp tục bị loại bỏ một lần nữa.
3. Kế tiếp, `>>` tiến hành đọc nhiều ký tự liên tiếp nhất có thể, cho đến khi nó chạm phải một ký tự xuống dòng (*newline*) hoặc một ký tự không hợp lệ với kiểu dữ liệu của biến.

    Trong trường hợp không đọc được bất kỳ ký tự nào hợp lệ ở bước trên (chẳng hạn bạn nhập chữ `a` trong khi biến `y` yêu cầu kiểu `int`), hệ thống sẽ xử lý theo 3 bước sau:
    * Biến nhận dữ liệu sẽ tự động được gán giá trị bằng 0 (quy định từ chuẩn C++11).
    * Ký tự lỗi `a` vẫn bị để lại và kẹt trong *input buffer*.
    * `std::cin` lập tức rơi vào trạng thái lỗi (*failure mode*) cho đến khi hàm `clear()` được gọi. Trong suốt thời gian này, mọi yêu cầu trích xuất dữ liệu tiếp theo đều bị ngó lơ, dẫn đến việc chương trình tự động bỏ qua các *input prompt* kế tiếp một cách im lặng thay vì dừng lại chờ bạn nhập.
4. Cuối cùng, những ký tự chưa được đọc (bao gồm cả ký tự *newline*) vẫn nằm chờ trong *input buffer* và sẵn sàng cho lần gọi `std::cin >>` tiếp theo.


## Switch-case

* Bạn được phép khai báo (*declaration*) nhưng không được phép khởi tạo giá trị (*initialization*) cho biến ngay phía dưới một `case` label. Tuy nhiên, việc khởi tạo này lại hoàn toàn hợp lệ nếu đặt bên trong một *explicit block* (sử dụng cặp ngoặc nhọn `{}`).


## `goto` statement

* Nếu thực hiện nhảy cóc về phía trước (*jump forward*), bạn không được phép nhảy qua vị trí *initialization* của bất kỳ biến nào 
  mà biến đó vẫn đang còn nằm trong *scope* tại điểm đích được nhảy đến.


## `for` loop

* Thứ tự thực thi (*order of execution*) cụ thể như sau:

    ```
    for (init-statement; condition; end-expression)
        statement;
    ```
    1. Init-statement: Chỉ diễn ra duy nhất một lần khi vòng lặp bắt đầu được khởi tạo.
    2. Condition: Với mỗi lần lặp (*loop iteration*), điều kiện này sẽ được kiểm tra và đánh giá. Nếu kết quả là `true`, phần lệnh (*statement*) mới được thực thi.
    3. Loop body: Phần thân vòng lặp (tức là lệnh *statement*) chính thức được chạy.
    4. End-expression: Được thực thi ngay sau khi *statement* chạy xong, sau đó luồng xử lý sẽ quay ngược trở lại bước kiểm tra điều kiện (*condition*).


## Constant expression

* **Constant expression** là một biểu thức **bắt buộc** phải có thể tính toán và đánh giá được ngay tại compile-time.
* Từ khóa `constexpr` nghĩa là: object đó đủ điều kiện để sử dụng bên trong một constant expression.
* **Constexpr variable**:
    * Bắt buộc phải được khởi tạo bằng một constant expression.
    * Mặc định được hiểu là một biến `const` (implicitly const).
    * Có thể được khởi tạo bằng một giá trị non-`const` (chẳng hạn như một literal).
* **Constexpr functions**:
    * Là hàm **có thể** được gọi bên trong một constant expression (ngược lại, các hàm non-`constexpr` hoàn toàn không thể gọi được trong constant expression).
    * Giá trị trả về của một hàm non-constexpr sẽ không được xem như là một constant expression.
    * Để hàm có thể thực thi ngay tại compile-time, cần phải thỏa mãn thêm hai điều kiện sau:
        * Các đối số truyền vào (arguments) phải là các constant expression.
        * Tất cả các câu lệnh bên trong hàm đều phải có thể xử lý được tại compile-time.
* Một *forward declaration* không thể khai báo là `constexpr`, bởi vì compiler bắt buộc phải biết toàn bộ phần định nghĩa (*definition*) cụ thể của hàm/biến đó thì mới tính toán được tại compile-time.
* Các parameter của một constexpr function không được phép khai báo là `constexpr` (và chúng cũng không tự động mang tính chất `constexpr`). 
    * Điều này có nghĩa là bạn không thể sử dụng các parameter này trong các constant expression khác nằm bên trong hàm:
        
        ```C++
        constexpr int foo(int b)    // b không phải là constexpr
        {
            constexpr int b2 { b }; // compile error: b không thể dùng trong các constant expression
        }
        ```
    * Tuy nhiên, các parameter này vẫn có thể được dùng làm đối số khi gọi một constexpr function khác:
        
        ```C++
        constexpr int goo(int c) { return c; }

        // b không phải là một constant expression trong phạm vi của foo(), nhưng goo() vẫn sẽ được tính toán tại compile-time nếu foo() được gọi tại compile-time
        constexpr int foo(int b) { return goo(b); }

        int main()
        {
            constexpr int a { foo(5) };     // foo(5) bắt buộc phải được tính toán tại compile-time
        }
        ```
* Khi một constexpr function được gọi bên trong một biểu thức non-constant expression, compiler có quyền tự quyết định xem có tính toán hàm đó tại compile-time hay không. Từ khóa `consteval` (C++20) ra đời để ép buộc compiler bắt buộc phải xử lý hàm tại compile-time.


## Storage duration

* *Global variable* là các biến được định nghĩa ***bên ngoài tất cả các hàm***. Chúng cũng có thể được khai báo bên trong một *namespace*.
* **Storage duration** quyết định thời điểm và cách thức mà một biến được khởi tạo và bị hủy bỏ.
    * **Automatic duration**: Biến được tạo ra ngay tại vị trí định nghĩa và sẽ bị giải phóng khi đi ra khỏi khối lệnh (*block*) chứa nó.
    * **Static duration**: Biến được tạo ra ngay khi chương trình khởi động (trước cả khi hàm `main()` bắt đầu chạy) và chỉ bị hủy khi chương trình kết thúc.
* Các *local variable* mặc định sẽ có thuộc tính **automatic duration**.
* Các *global variable* mặc định sẽ có thuộc tính **static duration**.
* Riêng các *static local variable* thì vừa có **static duration** (giống *global variable*), nhưng đồng thời lại vừa mang **local scope** (giống *local variable*).


## Preprocessor

* Trước khi quá trình biên dịch (*compilation*) chính thức diễn ra, mọi *code file* đều phải đi qua một giai đoạn sơ chế gọi là tiền xử lý (*preprocessing*).
* Một ***translation unit*** chính là trạng thái của ***một file đơn lẻ*** sau khi *preprocess* và ***ngay trước khi compile***.
* Khi hoạt động, *preprocessor* sẽ quét qua *code file* ***tuần tự từ trên xuống dưới*** để xử lý các ***preprocessor directive*** (những dòng bắt đầu bằng `#`):
    * `#include`: Thay thế chính dòng `#include` đó bằng ***toàn bộ nội dung*** của *file* được chỉ định.
    * `#define`: Gồm 2 loại chính: *object-like macro* và *function-like macro*.


## Phạm vi hoạt động (Scope) của các directive

* `#include` có thể "sao chép" các *directive* khác từ *file* được nhúng vào trong *file* hiện tại.

    => Nếu bạn `#define` một macro trong một file A, rồi `#include` file A đó vào một file B, thì *macro* này cũng sẽ khả dụng trong file B.
* Các *directive* chỉ có hiệu lực kể từ vị trí nó được khai báo cho đến hết *file* chứa nó.
    
    => Các *directive* được định nghĩa ở file A sẽ không ảnh hưởng hay lan sang file B được biên dịch độc lập (trừ khi A được `#include` vào B).


## One-Definition Rule (ODR)

* Một ***identifier*** của biến hoặc hàm chỉ được phép có duy nhất một *definition* (quy tắc này không áp dụng đối với *declaration*):
	* Nếu các *identifier* trùng tên xuất hiện trong cùng một *file*, hệ thống sẽ ngay lập tức báo lỗi biên dịch (*compiler error*).
	* Nếu các *identifier* trùng tên nằm ở các *file* khác nhau trong cùng một chương trình (*program*) => sẽ gây ra lỗi liên kết (*linker error*):
	    * Khi biên dịch, *compiler* sẽ xử lý từng *file* (ví dụ: `a.cpp` và `main.cpp`) một cách độc lập, do đó quá trình *compile* từng *file* riêng lẻ vẫn diễn ra suôn sẻ và không gặp lỗi gì.
	    * Tuy nhiên, khi sang giai đoạn linking, *linker* sẽ kết nối tất cả các *definition* từ `a.cpp` và `main.cpp` lại với nhau. Lúc này, nó sẽ phát hiện ra sự xung đột do có các *definition* trùng tên.
* Tuy nhiên, các ***kiểu dữ liệu*** (*types* — bao gồm cả *program-defined types*) sẽ được miễn trừ khỏi một phần của quy tắc ODR này. Ví dụ:
    * Định nghĩa cùng một *type* vào nhiều *translation unit* khác nhau không vi phạm ODR, nhưng
    * Định nghĩa cùng một *type* từ hai lần trở lên vào trong cùng một *translation unit* đơn lẻ thì vi phạm ODR (đó là lí do cần đến ***header guards***).


## Namespace

* **Namespace**: dùng để tránh trùng tên (*naming conflicts*).
* Nếu `::` được sử dụng mà không đi kèm tên namespace, ví dụ `::doSomething`, hệ thống sẽ tìm kiếm `doSomething` trực tiếp trong *global namespace*.
* Nếu không dùng `::`, *compiler* sẽ ưu tiên tìm từ trong ra ngoài: *namespace* hiện tại > các namespace bao quanh > *global namespace*.
* C++ cho phép định nghĩa nhiều khối *namespace* trùng tên, chúng sẽ được gộp lại.
* **Unnamed namespace**: Tất cả nội dung được khai báo bên trong một *unnamed namespace* coi như thuộc về *parent namespace*.
* **Inline namespace**: (Cơ chế rất giống với *unnamed namespace*) Mọi nội dung khai báo bên trong một *inline namespace* cũng coi như thuộc về *parent namespace*. Điểm khác biệt là *inline namespace* có thể được tận dụng để quản lý các phiên bản mã nguồn (*versioned*).


## Linkage

* **Linkage** của một *identifier* quyết định xem nó có thể được nhìn thấy và sử dụng bởi các *translation unit* khác hay không.
* **Internal linkage**: *Identifier* chỉ có thể được nhìn thấy và sử dụng trong phạm vi của một **translation unit** duy nhất, các *translation unit* khác hoàn toàn không thể truy cập được. Điều này đồng nghĩa với việc nếu 2 *source file* cùng sở hữu các *identifier* có *internal linkage* trùng tên nhau, chúng vẫn được xử lý độc lập và không hề xung đột.
* Các *global variable* mang thuộc tính *internal linkage* được gọi là **internal variable**.
* Các *global variable* mang thuộc tính *external linkage* được gọi là **external variable**.
* Các thiết lập mặc định (By default):
    * Các *non-constant global variable* mặc định sẽ có *external linkage*: `int g_x1{};`. 
        
        Bạn có thể chuyển nó sang *internal linkage* bằng cách dùng *keyword* `static`: `static int g_x1{};`.
    * Các *const global variable* mặc định lại có *internal linkage*: `const int g_x2{};`.

        Bạn có thể ép nó chuyển sang *external linkage* bằng cách dùng *keyword* `extern`: `extern const int g_x2{};`.
    * Các *constexpr global variable* mặc định cũng có *internal linkage*: `constexpr int g_x3{};`.
    
        Bạn có thể chuyển nó sang *external linkage* bằng cách dùng *keyword* `extern`: `extern constexpr int g_x3{};`.
    * Các *inline variable* mặc định sẽ có *external linkage*.
    * Các hàm (*functions*) mặc định sẽ có *external linkage*: `void doSomething();`.
    
        Hàm cũng có thể được chuyển sang *internal linkage* bằng cách thêm *keyword* `static`: `static void doSomething();`.

* Để sử dụng một *external identifier* đã được định nghĩa ở một *file* khác:
    * Đối với *external global variable*: Bạn bắt buộc phải đặt một *forward declaration* cho biến đó bằng cách dùng *keyword* `extern` và không kèm theo giá trị khởi tạo.
    * Đối với *external function*: Bạn chỉ cần khai báo *forward declaration* cho hàm đó mà không cần thêm *keyword* `extern`.
* Tất cả các *identifier* nằm bên trong một *unnamed namespace* đều được đối xử như thể chúng mang thuộc tính *internal linkage*:

    ```C++
    namespace // unnamed namespace
    {
        void doA() // chỉ có thể truy cập được trong file này
        {
            std::cout << "v1\n";
        }
    }
    // tương đương với:
    // static void doA()
    // ...
    ```


## Function overhead và inline expansion (Góc nhìn lịch sử)

* Ví dụ cụ thể:

    ```C++
    int min(int x, int y)
    {
        return (x < y) ? x : y;
    }
    ```
    1. Khi gặp một lời gọi hàm `min()`, CPU bắt buộc phải lưu lại địa chỉ của instruction hiện tại đang thực thi cùng với giá trị của các CPU register khác nhau. Kế tiếp, các parameter x và y mới được cấp phát vùng nhớ (instantiated) và khởi tạo giá trị (initialized).
    2. Sau đó, luồng thực thi (execution path) phải nhảy đến đoạn code nằm trong hàm `min()`. Khi hàm này kết thúc, chương trình lại phải nhảy ngược trở lại vị trí gọi hàm ban đầu, đồng thời giá trị trả về (return value) phải được copy ra ngoài để sử dụng.
* Tất cả những công việc phụ phát sinh để thiết lập (setup), hỗ trợ thực thi (facilitate), và/hoặc dọn dẹp (cleanup) sau khi hoàn thành một tác vụ nào đó được gọi chung là **overhead**.
* Đối với các hàm nhỏ (như hàm `min()` ở trên), chi phí cho phần *overhead* thậm chí có thể lớn hơn cả thời gian thực tế cần để chạy đoạn code bên trong hàm! Nếu hàm này được gọi liên tục, nó sẽ gây sụt giảm hiệu năng đáng kể so với việc bạn viết trực tiếp đoạn code đó tại chỗ (in-place).
* **Inline expansion** là quá trình mà một lời gọi hàm sẽ được thay thế trực tiếp bằng chính đoạn code định nghĩa (definition) của hàm đó.
* Về mặt lịch sử, các compiler ngày xưa không quá thông minh trong việc tự quyết định xem có nên áp dụng *inline expansion* hay không, đó là lý do vì sao từ khóa `inline` được ra đời. Tuy nhiên, các C++ compiler hiện đại ngày nay trong phần lớn trường hợp đều tối ưu tốt hơn con người, vì vậy ta thường sẽ ngó lơ mục đích này khi đề cập tới `inline`.


## Inline function và inline variable (Góc nhìn hiện đại)

* Từ khóa `inline` ngày nay được sử dụng để loại bỏ lỗi vi phạm quy tắc ODR: một inline function là hàm được phép *định nghĩa* (defined) ở nhiều translation unit khác nhau.
* Các yêu cầu bắt buộc đối với một `inline` function:
    1. Inline function bắt buộc phải có phần *definition* đầy đủ trong mọi translation unit có sử dụng nó.
    2. Mọi bản definition của cùng một inline function bắt buộc phải giống hệt nhau. Nếu không, chương trình sẽ gặp lỗi undefined behavior.
* Sau đó, linker sẽ tiến hành lọc bỏ các bản trùng lặp (de-duplicate) và chỉ giữ lại một định nghĩa duy nhất.
* Các `constexpr` function mặc định được xem là inline (implicitly inline). Lý do là vì compiler cần biết rõ phần definition của hàm trong mọi translation unit có sử dụng nó để có thể tính toán và đánh giá dữ liệu ngay tại compile time.
* Các `constexpr` variable không tự động được xem là inline (not implicitly inline).
* Các member function được định nghĩa **bên trong** (inside) phần định nghĩa của class sẽ **mặc định** là inline.
* Các member function được định nghĩa **bên ngoài** (outside) phần định nghĩa của class sẽ **không mặc định** là inline.
* Các constexpr member variable của một class cũng **mặc định** là inline.


## Exit

* Hàm `std::exit()` giúp chương trình kết thúc một cách bình thường (**terminate normally**).
* Lưu ý rằng "terminate normally" != chạy thành công. Nó vẫn có thể trả về một *status code* khác 0 (báo lỗi) nhưng quá trình kết thúc vẫn được tính là diễn ra bình thường.
* Hàm `std::exit()` được ngầm gọi (*implicitly*) ngay sau khi hàm `main()` return.
* `std::exit()` thực hiện một số tác vụ dọn dẹp (*cleanup function*):
    * Các object có *static storage duration* sẽ bị hủy (*destroyed*).
    * Đóng các file liên quan nếu chương trình có thao tác với file.
    * ⚠️ Nó hoàn toàn không dọn dẹp các *local variable*.
* Hàm `std::atexit()` dùng để đăng ký một hàm để tự động kích hoạt khi `std::exit()` được gọi.
* Hàm `std::abort()` khiến chương trình kết thúc một cách bất thường ("abnormally") — ví dụ: lỗi chia cho 0. Nó không thực hiện bất kỳ công đoạn dọn dẹp nào.
* Hàm `std::terminate()` thường được gọi ngầm định khi có một *exception* không được xử lý (*unhandled exception*). Theo mặc định, `std::terminate()` sẽ gọi trực tiếp đến `std::abort()`.


## `assert` và `static_assert`

* Khi một *assertion* thất bại (*fail*), chương trình lập tức kết thúc thông qua hàm `std::abort()`.
* C++ đi kèm một *macro* tích hợp sẵn tên là `NDEBUG`: nếu *macro* này được định nghĩa, tất cả các lệnh `assert` sẽ tự động bị vô hiệu hóa (*disabled*).

    ```C++
    #undef NDEBUG // bật lại các lệnh assert (bắt buộc phải đặt trước các dòng #include)
    ```
* Lệnh `static_assert` được kiểm tra ngay từ *compile-time* chứ không phải chờ đến *runtime* => vì vậy, bắt buộc phải truyền vào một *constant expression*.


## Kiểu dữ liệu cơ bản (Fundamental data types)

* Chuẩn C++ không quy định kích thước chính xác (tính theo bit) cho bất kỳ fundamental type nào.
* WARNING: `std::int8_t` và `std::uint8_t` thường có hành vi hoạt động giống hệt như các kiểu `char`.
* Các fixed-width integer thực chất không định nghĩa loại type mới — chúng chỉ là các alias cho các integral type sẵn có.
* Các type tốn ít memory hơn chưa chắc đã chạy nhanh hơn các type tốn nhiều memory. CPU thường được tối ưu hóa để xử lý dữ liệu ở một kích thước nhất định (ví dụ: 32 bit).
* Phân biệt giữa **integer** và **integral**:
    * **integer**: Chỉ một nhóm rộng bao gồm `short`, `int`, `long`, `long long`.
    * **integral**: Nghĩa là “dạng như số nguyên”, bao gồm một tập hợp rộng hơn các type được lưu trữ trong memory dưới dạng số nguyên, tính cả `bool` và `char`.
* Các kiểu fast và least integral types. Ví dụ:
    * `std::int_fast32_t`: Trả về signed integer type nhanh nhất (được CPU xử lý tối ưu nhất) có kích thước tối thiểu là 32-bit.
    * `std::int_least32_t`: Trả về signed integer type tốn ít memory nhất có kích thước tối thiểu là 32-bit.
* Lệnh `sizeof()` trả về một giá trị thuộc kiểu `std::size_t` — đây thực chất là một **alias** cho một *implementation-defined* **unsigned** integral type.
* Các floating point number:
    * `float`: Hầu như luôn được triển khai bằng định dạng single-precision IEEE 754 chuẩn 4-byte.
    * `double`: Hầu như luôn được triển khai bằng định dạng double-precision IEEE 754 chuẩn 8-byte.
    * `long double`: Trên các platform khác nhau, kích thước của nó có thể biến động từ 8 đến 16 byte hoặc có thể không dùng định dạng chuẩn IEEE 754.
* Các giá trị Boolean được **lưu trữ** và **xem như là** (evaluated to) các integral value: là 0 và 1, chứ không phải `true` hay `false`.


## Implicit type conversions

* Có 4 loại **standard conversions**:
    * Numeric promotions
    * Numeric conversions
    * Arithmetic conversions 
    * Other conversions
* Khi cần chuyển đổi kiểu, compiler có thể áp dụng 0, 1 hoặc 2 standard conversions.
* **Numeric promotions** áp dụng cho một số trường hợp *cụ thể* từ kiểu nhỏ sang kiểu lớn hơn:
    * `float` -> `double`
    * `signed char`, `signed short` -> `int`
    * `unsigned char`, `char8_t`, `unsigned short` -> `int` (nếu `int` chứa được mọi giá trị của kiểu ban đầu, ngược lại thì thành `unsigned int`)
    * `bool` -> `int` (`false` thành `0`, `true` thành `1`)

    Không phải mọi phép mở rộng (ví dụ: `char` lên `short`, hoặc `int` lên `long`) đều là numeric promotions, vì chúng không giúp chuyển đổi *hiệu quả*.

    ✅ Numeric promotions bảo toàn giá trị nên rất an toàn, giúp giảm mã thừa. Bạn chỉ cần viết `void printInt(int x)` và có thể truyền `short`, `char` vào mà không cần viết thêm `void printShort(short x)` hay `void printChar(char x)`.

* **Numeric conversions**:
    * Số nguyên -> Số nguyên bất kỳ (trừ các trường hợp thuộc integral promotions)
    * Số thực -> Số thực bất kỳ (trừ các trường hợp thuộc floating point promotions)
    * Số thực -> Số nguyên bất kỳ
    * Số nguyên -> Số thực bất kỳ
    * Số nguyên / Số thực -> `bool`

    Numeric conversions chia làm 3 loại:
    * Bảo toàn giá trị (Value-preserving conversions):
        * ✅ Compiler không cảnh báo.
        * ✅ Kiểu đích chứa được toàn bộ dải giá trị của kiểu gốc.
        * ✅ Có thể ép kiểu ngược lại mà không mất dữ liệu. Ví dụ: `int` -> `long` -> `int`.
    * Chuyển đổi diễn giải lại (Reinterpretive conversions):
        * ⚠️ Compiler có thể không cảnh báo.
        * ⚠️ Kiểu đích không chứa được toàn bộ giá trị của kiểu gốc.
        * ✅ Có thể ép kiểu ngược lại mà không mất dữ liệu. Ví dụ: `int` -> `unsigned int` -> `int`.
    * Chuyển đổi mất dữ liệu (Lossy conversions): Ví dụ: `int` -> `float` -> `int`.
        * ❌ Compiler sẽ cảnh báo.
        * Lạ một điều, chuyển từ số thực sang số nguyên luôn bị coi là narrowing (thu hẹp), kể cả khi giá trị biểu diễn được chính xác.
            ```C++
            int n { 5.0 }; // Lỗi compile: narrowing conversion
            ```
        * Và cũng lạ là, chuyển từ số thực lớn sang số thực nhỏ hơn lại không bị coi là narrowing, dù có mất mát độ chính xác.
            ```C++
            constexpr double d { 0.1 };
            float f { d }; // Không phải narrowing, dù độ chính xác bị giảm
            ```

* **Arithmetic conversions**: ví dụ: `??? y { 2 + 3.5 };`
    * Một số toán tử yêu cầu các operand phải cùng kiểu. Một (hoặc cả hai) operand sẽ được implicit convert sang **common type** thông qua quá trình **usual arithmetic conversions**.
    * Compiler xếp hạng các kiểu như sau (rút gọn):
        1. `long double` (cao nhất)
        2. `double`
        3. `float`
        4. `long long`
        5. `long`
        6. `int` (thấp nhất)
    * Quy tắc tìm **matching type**:
        1. Bước 1:
            * Nếu có 1 operand kiểu **nguyên** và 1 operand kiểu **thực**, operand kiểu nguyên sẽ chuyển sang kiểu của operand thực (không có integral promotion).
            * Nếu không, mọi operand kiểu nguyên sẽ được promote (numeric promotion).
        2. Bước 2:
            * Sau khi promote, nếu có 1 operand signed và 1 unsigned, áp dụng quy tắc đặc biệt:
                * Nếu rank của kiểu unsigned >= rank của kiểu signed: operand signed sẽ được convert sang kiểu unsigned.
                * Nếu kiểu signed chứa được mọi giá trị của kiểu unsigned: operand unsigned sẽ được convert sang kiểu signed.
                * Nếu không: Cả hai được convert sang kiểu unsigned tương ứng của kiểu signed.
            * Nếu không thuộc các trường hợp trên, operand rank thấp sẽ convert sang kiểu của operand rank cao.

* Other conversion:
    * Xem phần **converting constructor** bên dưới.


## Function overloading

* **Function overloading**: Nhiều hàm cùng tên nhưng khác nhau về số tham số hoặc kiểu tham số. Mỗi hàm như vậy được gọi là một **overloaded function** (hoặc **overload**).
* **Signature** (Chữ ký hàm) = Tên hàm + Số lượng tham số + Kiểu tham số + Các function-level qualifiers.
* **Overload resolution**: là quá trình compiler chọn đúng overload phù hợp nhất với lời gọi hàm. Thứ tự ưu tiên:
    1. Hàm khớp chính xác (exact match), bao gồm cả việc cho phép các **trivial conversions** (như chuyển thành `const` hoặc reference). Ví dụ:

        ```C++
        void foo(int);
        void foo(double);
        foo(5); // exact match với foo(int)
        foo(5.0); // exact match với foo(double)
        ```

        ```C++
        void foo(const int);
        void foo(const double&); // reference
        foo(5); // exact match với foo(const int) qua trivial conversion
        foo(5.0); // exact match với foo(const double&) qua trivial conversion
        ```

        ```C++
        void foo(int);
        void foo(const int&);

        foo(5); // ambiguous match (lỗi do tối nghĩa, compiler không biết chọn hàm nào)
        ```
    2. Thử **numeric promotion**.
    3. Thử **numeric conversion**.
    4. Thử **user-defined conversions**.
    5. Thử ellipsis (`...`).
    6. Nếu tất cả đều thất bại, compiler sẽ báo lỗi.
* Nguyên tắc khớp cho hàm có nhiều tham số: 
    * Compiler áp dụng các quy tắc trên cho *lần lượt từng* đối số.
    * Hàm chiến thắng phải khớp tốt hơn mọi hàm ứng viên khác ở ít nhất 1 tham số, và không được kém hơn ở tất cả các tham số còn lại.


## Value categories 

* Mọi expression trong C++ đều có 2 thuộc tính: type và value category.
* Value category:
	* **lvalue**: là một đối tượng mà ta có thể truy cập được thông qua địa chỉ.
	* **rvalue**: là giá trị tạm thời, không thể truy cập thông qua địa chỉ, và bị huỷ ngay khi kết thúc biểu thức chứa nó. 
    ```C++
    int x { 5 };     // 5 là rvalue
    int y { x };     // x là lvalue
    int z { x + 1 }; // (x + 1) là rvalue
    int t{ return5() }; // return5() là rvalue
    ```
    Nói "rvalue không có địa chỉ" là đang nói ở góc độ ngôn ngữ lập trình, chứ không phải ở góc độ phần cứng vật lý. Nó vẫn có thể nằm ở đâu đó trên bộ nhớ, nhưng C++ chủ động ẩn địa chỉ đó đi.
* **Lvalue-to-rvalue conversion**: Phép gán `=` yêu cầu vế phải phải là một rvalue. Tuy nhiên lệnh `x = y;` vẫn hợp lệ do lvalue `y` sẽ được implicit convert thành rvalue.
* Khác với các **literals** thông thường (vốn là rvalue), C-style string **literal** lại là một lvalue vì nó sẽ decay thành một pointer.


## References

* **Reference** là một **alias** của một object đã tồn tại.
* Reference không phải là object. Do đó, không có khái niệm reference trỏ tới một reference (reference to reference).
* Khai báo reference:
    * Bắt buộc **phải khởi tạo** khi khai báo. 
    * Sau khi khởi tạo, **không thể reseat** (không thể gán lại để trỏ sang object khác).
* Thao tác bind một reference rất nhẹ về mặt hiệu năng.
* Gán một reference cho một biến non-reference sẽ tạo **copy**.
    ```C++
    int x { 5 };
    int& ref { x };
    int y { ref }; // y bây giờ là bản copy của x
    std::cout << &x << '\n';    // 0x7ffc70904a60
    std::cout << &ref << '\n';  // 0x7ffc70904a60 (giống x)
    std::cout << &y << '\n';    // 0x7ffc70904a64 (khác x)
    ```
* **Lvalue reference** là alias của một lvalue. Có thể đọc/ghi giá trị của object thông qua reference.
* Lvalue và `const`:
	* ⚠️ Thuật ngữ:
	   	* **Lvalue reference to (a) non-const** có thể được gọi bằng cái tên khác là:
	        * **non-const lvalue reference**
	        * ⚠️ **lvalue reference**
	    * **Lvalue reference to (a) const** có thể được gọi bằng cái tên khác là:
	        * **const lvalue reference**
	* **Lvalue reference to const**:
   		* coi object mà nó trỏ tới là `const` (bất kể bản thân object đó có phải là `const` hay không).
       	* ⚠️ có thể được khởi tạo bằng một rvalue:
	        ```C++
	        const int& ref_rvalue { 5 }; // Hợp lệ, lvalue reference to const có thể khởi tạo từ rvalue
	        ```
       	 	Khi đó:
       	  	* Vòng đời của rvalue được kéo dài bằng vòng đời của reference `ref_rvalue`.
       	  	* Địa chỉ của rvalue đó lộ ra:
       	  		```C++
       	  	 	const int& ref_rvalue { 5 };

       	  	 	// Compiler tự động tạo một biến __temp và buộc vòng đời của __temp chết cùng lúc với ref_rvalue
			    // int __temp = 5;
			    // const int& ref_rvalue = __temp;

       	  	 	// Lúc này ref có địa chỉ RAM bình thường:
    			std::cout << "Dia chi tren RAM: " << &ref;
       	  	 	```
	  	* ⚠️ nếu được khởi tạo bằng một giá trị **khác kiểu**, compiler sẽ tạo ra một temporary object có cùng kiểu với reference và bind reference vào object tạm đó:
	        ```C++
	        const double& r1 { 5 };
	        std::cout << r1 << '\n'; // in ra 5
	       
	        char c { 'a' };
	        const int& r2 { c };     
	        std::cout << r2 << '\n'; // in ra 97
	       
	        short s { 6 };
	        const int& r3 { s };
	        s--;          // r3 không bị đổi giá trị, vì r3 đang bind vào một bản copy tạm thời (temporary copy)
	        std::cout << s << r3 << '\n'; // 56
	        ```
	        => reference không phải lúc nào cũng bind trực tiếp vào đúng object ban đầu.

* **R-value references**:
    * Là reference được khởi tạo bằng một r-value. **Không thể** được khởi tạo bằng l-value:
        ```C++
        int x{ 5 };
        int& lref{ x }; // l-value reference
        int&& rref{ 5 }; // r-value reference
        ```
    * Bản thân các ***biến*** (variables) mang kiểu rvalue reference lại được tính là **lvalues**.
        ```C++
        int&& ref{ 5 }; // r-value reference
        func2(ref); // in "l-value reference"!!!
        ```
  	* So sánh với "**lvalue reference to const** được khởi tạo bằng một rvalue":
  		```C++
		const int& lref { 5 };	// **lvalue reference to const** được khởi tạo bằng một rvalue
		int&& rref{ 5 }; 		// r-value reference

  	 	// Cơ chế diễn giải của compiler cho *rvalue reference* y hệt **lvalue reference to const**, chỉ khác là bỏ `const` đi
  	 	// int __temp = 100;
  	 	// int& rref = __temp;
  	 	```
  	 	* Giống: kéo dài vòng đời.
  	  	* Khác:
  	  		* **l-value reference to const**:
  	  	 		* có thể khởi tạo bằng cả l-value và r-value.
  	  	 		* ✅ không thể sửa đổi giá trị
  	  	   	* **r-value references**:
  				* chỉ có thể khởi tạo bằng r-value.
  	  	   		* ✅ non-const **r-value reference** có thể sửa đổi giá trị

* Cho phép overload hàm riêng rẽ cho l-value và r-value:
	```C++
	void func2(int& x)  { std::cout << "l-value reference" << '\n'; }
	void func2(int&& x) { std::cout << "r-value reference" << '\n'; }

	int x{ 5 };
	func2(x); // => "l-value reference"
	func2(5); // => "r-value reference"
	```


# Pointers

* **Pointer** là một **object** lưu trữ địa chỉ bộ nhớ.
* Toán tử:
	* address-of (`&obj`) trả về một pointer có type suy ra từ `obj`.
	* dereference (`*ptr`) một **lvalue** biểu diễn đối tượng mà con trỏ `ptr` đang trỏ tới.
* ✅ **Void pointer** (hay **generic pointer**): loại pointer đặc biệt có thể trỏ tới object thuộc bất kỳ kiểu dữ liệu nào!
    * Bắt buộc phải cast sang kiểu pointer cụ thể trước khi dùng toán tử dereference.
    ```C++
    int nValue {};
    double dValue { 5.5 };

    void* pValue {};
    pValue = &nValue;   // hợp lệ
    pValue = &dValue;   // hợp lệ 

    std::cout << *(static_cast<double*>(pValue)) << '\n';   // hợp lệ, phải cast trước khi dereference
    ```
* Pointer và `const`:
    * **Pointer to const**: Coi object mà nó trỏ tới là `const` (bất kể object đó có `const` thật hay không).
    * **Const pointer**: Bản thân pointer là `const`, không thể reseat (không thể đổi địa chỉ mà nó đang trỏ).
    * Có thể kết hợp thành **const pointer to a const**.
* Pointer có hành vi khá giống lvalue reference. Khác ở chỗ:
    * Reference bắt buộc phải khởi tạo; Pointer thì không.
    * Reference không phải là object; Pointer là object.
    * Reference không thể gán lại (reseat); Pointer có thể trỏ đi nơi khác.
    * Reference luôn phải bind vào một object; Pointer có thể không trỏ đi đâu (`nullptr`).
    * Reference an toàn hơn khi sử dụng so với Pointer.
* Thực tế, sâu bên dưới, compiler thường implement reference bằng pointer. Do đó, bản chất C++ luôn truyền dữ liệu theo kiểu pass-by-value!
* Kích thước (size) của mọi pointer là như nhau, phụ thuộc vào kiến trúc hệ thống (32-bit hoặc 64-bit).
* Pointer arithmetic (Tính toán con trỏ):
    * Giả sử `ptr` có kiểu `int*`, và `int` chiếm 4 bytes:
        * `ptr + 1`: Trả về địa chỉ nằm sau `ptr` 4 bytes.
        * `ptr - 1`: Trả về địa chỉ nằm trước `ptr` 4 bytes.
        * Cú pháp `ptr[n]` tương đương với biểu thức `*((ptr) + (n))`
        
        => Đây là lý do C-style array cho phép dùng số nguyên âm làm index. Ví dụ: `ptr[-1]`.


## Function pointer

* Giống như variables, các function cũng được lưu tại một địa chỉ nhớ (memory address) cụ thể, nên chúng được tính là các lvalues.
    ```C++
    // code của foo bắt đầu tại địa chỉ 0x002717f0
    int foo() { return 5; }

    foo(); // nhảy tới địa chỉ 0x002717f0
    ```
* Khai báo pointer trỏ tới function (⚠️ cú pháp khá xấu):
    ```C++
    int goo() { return 6; }
    int hoo(int x) { return x; }

    int (*fcnPtr)();
    int (*fcnPtr2)(){ &foo };       // fcnPtr2 trỏ tới function foo
    int (*fcnPtr4)(int) { &hoo };   // fcnPtr4 trỏ tới function hoo

    auto fcnPtr9 { &hoo };  // int (*)(int)
    ```
* Type của function pointer bắt buộc phải khớp tuyệt đối với type của function:
    ```C++
    int hoo(int x) { return x; }

    int (*fcnPtr3)() { &hoo }; // lỗi
    int (*fcnPtr4)(int) { &hoo }; // hợp lệ
    ```
* Khi gọi tên một function (không kèm dấu ngoặc `()`), C++ sẽ tự động (implicitly) convert nó thành một function pointer:
    ```C++
    int hoo(int x) { return x; }

    int (*fcnPtr5)(int) { hoo }; // hợp lệ, tự động convert hoo thành function pointer
    void* fcnPtr6 { hoo };       // lỗi
    ```
* Gọi function thông qua function pointer có 2 cách: explicitly dereference và implicitly dereference:
    ```C++
    int (*fcnPtr2)(){ &foo }; // fcnPtr2 trỏ tới foo

    (*fcnPtr2)(); // explicitly dereference
    fcnPtr2();    // implicitly dereference
    ```
* Callback functions:
    ```C++
    void loo(int x, int y, bool (*fcnPtr)(int, int))
    // void loo(int x, int y, bool fcnPtr(int, int))    tương đương, nhưng ít được khuyên dùng hơn
    {
        fcnPtr(x, y);
    }

    bool moo(int x, int y) { return x > y; }

    loo(3, 4, &moo); // hợp lệ
    loo(3, 4, moo);  // hợp lệ
    ```
* Làm gọn cú pháp khai báo function pointer:
    * Dùng Type alias:
        ```C++
        using fcnPtrType = bool (*)(int, int);

        void loo2(int x, int y, fcnPtrType fcnPtr) {}
        ```
    * Dùng `std::function`:
        ```C++
        void loo3(int x, int y, std::function<bool(int, int)> fcnPtr) {}
        ```

        ```C++
        int soo() {}
        int zoo(int x) {}

        std::function<int()> fcnPtr7 { &soo }; // function pointer trả về int, không nhận tham số
        std::function fcnPtr8 { &zoo }; // hợp lệ nhờ CTAD (Class Template Argument Deduction)
        ```

        ```C++
        using fcnPtrType2 = std::function<bool(int, int)>;  // type alias
        ```
        
        Lưu ý: `std::function` chỉ cho phép gọi hàm bằng implicitly dereference (VD: `fcnPtr()`), không hỗ trợ explicitly dereference (VD: `(*fcnPtr)()`).


## Low-level const và top-level const

* **Low-level const**: Áp dụng cho object mà pointer trỏ tới hoặc reference tham chiếu tới.
* **Top-level const**: Áp dụng cho chính bản thân object đó.

    ```C++
    const int* ptr; // low-level const, áp dụng cho int
    const int& ref; // low-level const, áp dụng cho int

    const int x; // top-level const, áp dụng cho int
    int* const ptr; // top-level const, áp dụng cho pointer
    int& ref; // bản thân reference ngầm định (implicitly) luôn là top-level const

    constexpr const int& ref; // constexpr áp dụng cho reference (top-level), const áp dụng cho int (low-level)
    ```
* ⚠️ Việc loại bỏ reference (dropping a reference) có thể biến một low-level const thành top-level const. Ví dụ:
    
    ```C++
    const int&  // low-level const
    const int   // top-level const
    ```


## Type deduction

* Type deduction không bao gồm `const`/`constexpr`. Nếu muốn, phải khai báo tường minh (explicitly):

    ```C++
    const int a { 5 };
    auto b { a };      // b có kiểu int, không phải const int
    const auto e { a }; // phải chỉ định const tường minh
    ```
* Type deduction cũng loại bỏ (drop) references. Nếu muốn giữ reference, phải khai báo tường minh:

    ```C++
    int& getRef();
    auto x { getRef() }; // x có kiểu int, không phải int&
    auto& y { getRef() }; // phải chỉ định reference tường minh
    ```
* ⚠️ Type deduction chỉ drop top-level const, KHÔNG drop low-level const.
* Nếu initializer là một **reference to const**:
    1. Drop reference trước (có thể reapply ở bước sau nếu khai báo tường minh).
    2. Sau đó, drop các top-level const.

    ```C++
    const int& x { ... }; // x là "reference to const" int, low-level const

    auto ref1 { x }; // int. Giải thích: const int&  -> const int (drop reference) -> int (drop top-level const)
    const auto ref2 { x }; // const int. Giải thích: const int& -> const int (drop reference) -> int (drop top-level const) -> const int (reapply const)
    auto& ref2 { x }; //  const int&. Giải thích: const int& -> const int (drop reference) -> const int& (reapply reference) 
    ```

    ```C++
    constexpr const int& x { ... }; // constexpr là top-level, const là low-level

    auto ref1 { x }; // int. Giải thích: constexpr const int& -> constexpr const int (drop reference, lúc này cả constexpr và const đều thành top-level) -> int (drop top-level const)
    auto& ref2 { x }; // const int&. Giải thích: constexpr const int& -> constexpr const int (drop reference) -> constexpr const int& (reapply reference, lúc này chỉ constexpr là top-level) -> const int& (drop top-level const)
    ```
* Type deduction KHÔNG drop pointers (khác với references).

    ```C++
    int* x;

    auto y { x }; // int*, là pointer
    auto* z { x }; // int*, là pointer (tương tự như y nhưng cú pháp rõ ràng hơn)

    auto y { *x }; // int, không phải pointer
    auto* z { *x }; // lỗi compile: initializer không phải là pointer
    ```
* Type deduction cho C-style string:
    ```C++
    auto s1{ "Alex" };  // const char*
    auto* s2{ "Alex" }; // const char*
    auto& s3{ "Alex" }; // const char(&)[5]
    ```
    
* Function có return type là `auto` phải được fully defined (định nghĩa hoàn chỉnh) trước khi được gọi, chỉ forward declaration là không đủ. Nếu muốn forward declare, ta phải khai báo return type một cách tường minh:
    ```C++
    auto add(int x, double y) -> std::common_type_t<decltype(x), decltype(y)>;
    ```
    ```C++
    template <typename T, typename U>
    auto max(T x, U y) -> std::common_type_t<T, U>;
    ```


## Program-defined types: Enumerated types

* **Unscoped enumerations**:
    * Mặc định (implicitly) là `constexpr`.
    * Các enumerators nằm cùng scope với bản thân enumeration => Không thể dùng trùng tên enumerator cho nhiều enumerations khác nhau trong cùng một scope.
    * **Implicitly convert** (tự động chuyển) sang số nguyên (integral values). Mặc định enumerator đầu tiên mang giá trị 0, nhưng có thể gán giá trị tường minh (explicitly).

        ```C++
        enum Animal
        {
            cat = -3,    // giá trị có thể âm
            dog,         // -2
            horse = 5,
            giraffe = 5, // dùng chung giá trị với horse
            chicken,     // 6
        };
        ```
    * Số nguyên **không** implicitly convert ngược lại thành enumeration:

        ```C++
        Animal a1 { -3 };                       // lỗi: không tự động convert
        Animal a2 { static_cast<Animal>(-3) };  // hợp lệ, ép kiểu tường minh
        ```
    * ⚠️ Nếu dùng **zero-initialized**, enumeration sẽ nhận giá trị 0, kể cả khi không có enumerator nào mang giá trị 0:

        ```C++
        Animal a {}; // a được gán bằng 0
        ```
    * Hầu hết compiler mặc định dùng `int` làm underlying type (kiểu cơ sở). Nhưng ta có thể chỉ định rõ kiểu khác:
        
        ```C++
        enum Foo : std::int8_t
        {
            goo,
            boo,
        };
        ```
* **Scoped enumerations** (`enum class`):
    * KHÔNG implicitly convert sang số nguyên.
    * Các enumerators bị đóng gói hoàn toàn bên trong scope của chính enumeration đó.


## Program-defined types: Class types

* **Aggregate** vs **Non-aggregate**:
    * Trong lập trình nói chung: Aggregate là bất kỳ type nào chứa nhiều data members.
    * Trong C++: Aggregate khắt khe và hẹp hơn:
        * Không có user-declared constructors.
        * Không có private hoặc protected non-static data members.
        * Không có virtual functions.

* Các cách khởi tạo 1 **aggregate**:
	* Cách 1: Không khởi tạo (**default-initialization**):
		* Nếu có default member initializer => dùng default.
		* Nếu Không có default member initializer => member mang giá trị rác (**default-initialization**).
    * Cách 2: Dùng **initializer list**: 
        * Khởi tạo từng member một **theo đúng thứ tự khai báo** trong struct.
            ```C++
            struct Employee
            {
                // data members (hoặc member variables)
                int id {};
                int age {};
                double wage {};
            };

            Employee frank = { 1, 32, 60000.0 }; 	// copy-list initialization
            Employee alice { 2, 28, 45000.0 };     	// list initialization (khuyến khích)

            // gán (assignment)
            alice = { 2, 30, 4000.0 };

            Employee dummyEmployee() { return Employee { 1, 32, 60000.0 };}
            Employee dummyEmployee2() { return { 1, 32, 60000.0 }; }  // có thể bỏ qua tên type
            Employee dummyEmployee3() { return { }; } // value-initialize tất cả members
            ```
			* Nếu có giá trị khởi tạo tường minh (explicit) => dùng giá trị đó.
			* Nếu thiếu giá trị khởi tạo + CÓ default member initializer => dùng default.
			* Nếu thiếu giá trị khởi tạo + KHÔNG CÓ default member initializer => **value-initialization** (thường gán bằng 0/empty).
    * Cách 3: Khởi tạo từ một struct khác cùng type:

        ```C++
        struct Foo
        {
            int a {};
            int b {};
            int c {};
        };
        
        Foo f3 { 1, 2, 3};

        // Các cách dưới đây KHÔNG phải là aggregate initialization:
        Foo f4 = f3;    // copy initialization
        Foo f5 { f3 };  // direct-list initialization
        Foo f6(f3);     // direct-initialization
        ```
* Không thể dùng aggregate initialization cho các non-aggregate:

	```C++
	struct Date
	{
	private:	// => Date không phải là Aggregate
		int m_year {};     
		int m_month {};
	};

	Date today { 2020, 10 }; // Lỗi compile: Không phải aggregate initialization và Date cũng không có constructor tương ứng để xử lý.

	Date today2 {};   // Hợp lệ, gọi implicit default constructor
	```

* **Constructors**:
    * **Default constructor**:
    	* là constructor không có bất kỳ tham số nào, **HOẶC** có tham số và tất cả chúng đều có giá trị mặc định:
        ```C++
        struct Foo6
        {
            Foo6() 						// default constructor
        	// Foo6(int x=0, int y=0) 	// default constructor, tất cả đều có giá trị mặc định
            {}
        };
        ```
	    * **Implicit default constructor**: là **default constructor** do compiler tự động sinh ra. Nó không có member initializer list và có phần body rỗng.
      		* Với aggregate: luôn luôn có.
        	* Với non-aggregate: nếu không có bất kỳ user-declared constructor nào.

| Kiểu khởi tạo | Ví dụ | Aggregate | Non-aggregate |
| :--- | :--- | :--- | :--- |
| **default-initialization** | `Foo foo;` | Gọi default constructor [1] | Gọi default constructor [2] |
| **value-initialization** | `Foo foo{};` | ~ Aggregate Initialization với list rỗng [3] | Gọi default constructor |

    * **Delegating constructors** (Ủy quyền constructor). Trình tự thực thi:
        1. Quá trình khởi tạo được ủy quyền cho một constructor khác (delegated constructor):
            1. Chạy member initializer list của delegated constructor để khởi tạo các members.
            2. Chạy body của delegated constructor.
        2. Chạy body của delegating constructor (constructor gốc).
    * Constructor thực chất không làm nhiệm vụ tạo ra object. Việc cấp phát bộ nhớ (memory allocation) cho object đã được compiler thực hiện từ *trước khi* constructor được gọi.
    * ✅ Nếu constructor bị dừng/hủy (aborted) giữa chừng, tất cả các class members đã được tạo và khởi tạo thành công (trước khi chạy vào **body** của constructor) vẫn sẽ được destruct bình thường.
        
        Đây là một phần của nguyên lý [***RAII***](https://www.learncpp.com/cpp-tutorial/destructors).

* Các cách khởi tạo 1 **non-aggregate**:
    * Dùng **member initializer list**: ⚠️ Lưu ý: các members luôn được khởi tạo theo đúng **thứ tự khai báo** bên trong class, chứ không phải theo thứ tự từ trái sang phải trong list.

        ```C++
        class Foo3
        {
        private:
            int m_x {};
            int m_y {};

        public:
            Foo3(int x, int y)
                : m_y { std::max(x, y) }, m_x { m_y } // Lỗi logic ở dòng này do m_x được khởi tạo trước m_y
            {
            }

            void print() const { std::cout << "Foo(" << m_x << ", " << m_y << ")\n"; }
        };

        void func2()
        {
            Foo3 foo3{ 6, 7 };  // member initialization list
            foo3.print();       // Foo(6, 7)
        }
        ```
    * Các kịch bản khởi tạo:
        * Có mặt trong member initializer list -> Dùng giá trị đó.
        * Không có, nhưng có default member initializer -> Dùng giá trị default.
        * Không có cả hai -> Thực hiện **default-initialization**.
* **List constructor**:
    * Các containers (như `std::vector`) thường có một constructor đặc biệt gọi là **list constructor**, cho phép tạo instance bằng một **initializer list**.
        ```C++
        std::vector<int> primes{ 2, 3, 5, 7 };
        ```
    * Nó thực hiện 3 công việc (nếu cần):
        * Đảm bảo container được cấp phát đủ bộ nhớ (storage) để chứa tất cả giá trị khởi tạo.
        * Cài đặt chiều dài (length) của container bằng với số phần tử trong initializer list.
        * Khởi tạo các phần tử theo đúng thứ tự (sequential order).

        ```C++
        std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; //  Dùng CTAD (C++17) để tự suy luận (deduce) type là char (được khuyên dùng).
        ```
    * Luật ưu tiên đặc biệt của C++:
        * Nếu initializer list rỗng (`{}`) -> Ưu tiên gọi **default constructor** hơn list constructor.
        * Nếu initializer list có phần tử -> Ưu tiên gọi một **list constructor** phù hợp hơn các constructors khác.


* **Implicit object**:
    
    ```C++
    CDate today { 2020, 10, 14 };
    today.print();
    ```
    * Khi gọi `today.print()`, `today` chính là **implicit object**, và nó được implicitly truyền (pass) vào hàm `print()`.
    * Bên trong mọi member function, `this` là một const pointer lưu trữ địa chỉ của implicit object hiện tại.
        
        ```C++
        void print() const { std::cout << m_id; }       // dùng this kiểu implicit (ngầm định)
        void print() const { std::cout << this->m_id; } // dùng this kiểu explicit (tường minh)
        ```
    * Trong Java và C#, `this` được implement dưới dạng reference thay vì pointer.
* **Const member function**: là member function cam kết không thay đổi (modify) object và không gọi các non-const member functions khác.
    * Const objects không thể gọi non-const member functions, kể cả khi hàm đó thực tế không modify object.
    * Có thể overload để tạo ra 2 phiên bản const và non-const cho cùng một member function.
* Các member functions có thể được define (định nghĩa) theo thứ tự bất kỳ. Lý do là vì khi compiler đọc thấy một member function definition:
    1. Hàm đó sẽ được ngầm (implicitly) forward declared.
    2. Phần definition của hàm sẽ được dời xuống ngay sau khi kết thúc class definition.
* Access levels:
    * Mặc định, các members của một `struct` là `public`.
    * Mặc định, các members của một `class` là `private`.
    * ⚠️ C++ access levels hoạt động theo phạm vi class (per-class), không phải theo object (per-object). (Nghĩa là các object cùng class có thể truy cập private member của nhau).
* **Converting constructor**:
    * **Implicit conversion**: Ở ví dụ dưới, hàm `printFoo` nhận parameter kiểu `Foo`, nhưng ta lại truyền vào `int`. Khi compiler thấy `printFoo(5);`, nó sẽ tìm một hàm cho phép convert từ `int` sang `Foo`. Hàm đó chính là constructor `Foo(int)`.
        ```C++
        class Foo
        {
        private:
            int m_x{};
        public:
            Foo(int x)  // cho phép implicit conversion từ int sang Foo
                : m_x{ x }
            { }
        };

        void printFoo(Foo f) { }

        printFoo(5); // convert từ `5` thành `Foo { 5 }`
        ```
    * Compiler chỉ cho phép **tối đa 1** implicit user-defined conversion. Trong ví dụ dưới, `printEmployee("Joe");` sẽ báo lỗi vì nó cần tới 2 bước user-defined conversions: C-style string literal -> `std::string_view` -> `Employee`.
        ```C++
        class Employee
        {
        private:
            std::string m_name{};

        public:
            Employee(std::string_view name)
                : m_name{ name }
            { }
        };

        void printEmployee(Employee e) { }

        printEmployee("Joe");   // Lỗi compile: yêu cầu tới 2 user-defined conversions
        printEmployee( "Joe"sv);    // Hợp lệ, chỉ cần 1 user-defined conversion từ std::string_view sang Employee
        printEmployee(Employee{ "Joe" }); // Hợp lệ, chỉ cần 1 user-defined conversion từ C-style string literal sang std::string_view
        ```
    * Để ngăn chặn implicit conversion, dùng từ khóa `explicit` để báo compiler không được dùng constructor này làm converting constructor:
        ```C++
        class Dollars2
        {
        private:
            int m_dollars{};

        public:
            explicit Dollars2(int d) // đánh dấu explicit
                : m_dollars{ d }
            { }
        };

        void print2(Dollars2 d) { }

        print2(5); // Lỗi compile: không thể convert int sang Dollars2
        print2(static_cast<Dollars2>(5)); // Hợp lệ, ép kiểu explicit (tường minh)
        ```


## Templates

* Function templates bản chất không phải là hàm thực sự, chúng dùng để sinh ra (generate) hàm.
* Quá trình sinh hàm từ function templates được gọi là **instantiation**.
* Một **function instance** chỉ được instantiate **đúng 1 lần duy nhất** ở lần gọi hàm đầu tiên trong mỗi translation unit. Các lần gọi tiếp theo sẽ tái sử dụng instance đã được tạo.
* ⚠️ Cẩn thận với **modifiable static local variables** trong function templates: mỗi function được instantiate ra sẽ có một bản sao static local variable hoàn toàn độc lập.
* Function templates có thể được overload.
* **Non-type template parameter**: là template parameter có kiểu cố định, đóng vai trò như một placeholder cho một giá trị `constexpr`.
* Các function được implicitly instantiate từ template sẽ tự động là implicitly inline.
* Khi cần viết một implementation riêng cho một specific type:
    1. Cách 1 (không áp dụng cho class type): Định nghĩa một non-template function cho type đó. Khi tiến hành overload resolution, hàm này sẽ được ưu tiên hơn template function.
    2. Cách 2: Dùng **template specialization**. Cách này cũng đem lại kết quả tương tự (xem code trên github).
    
    **Partial template specialization**: Tính đến C++23, function không thể được partial specialize, chỉ class mới làm được điều này (xem code trên github).


## Program-defined types and header files

* Lưu ý đoạn code sau là một full definition, không phải forward declaration:
    ```C++
    struct Fraction
    {
        int numerator {};
        int denominator {};
    };
    ```
* Khác với functions (chỉ cần forward declaration là dùng được), header files thường phải chứa full definition của một class. Lý do: compiler cần biết cấu trúc khai báo của các members để đảm bảo chúng được sử dụng đúng cách, đồng thời cần tính toán chính xác kích thước object của type đó để tiến hành instantiate.
* Với non-template classes, quy chuẩn chung là đặt class definition vào header file, và phần member function definitions vào file `.cpp` cùng tên. Tuy nhiên, nếu áp dụng cách này cho templates, bạn sẽ gặp linker error. Lý do tóm tắt:
    1. C++ compile từng file một cách độc lập.
    2. Compiler chỉ instantiate một class template nếu nó thực sự được sử dụng (nghĩa là: compiler bắt buộc phải nhìn thấy đồng thời cả full class template definition chứ không chỉ declaration, VÀ các specific template type(s) đang cần dùng tới).

    => Do đó, compiler sẽ không instantiate template bên trong file `.cpp` để link với lời gọi từ `main.cpp`. Chi tiết xem [tại đây](https://www.learncpp.com/cpp-tutorial/template-classes/#:~:text=Splitting%20up%20template%20classes).
* Với template specialization: compiler phải nhìn thấy full definition của CẢ non-specialized class VÀ specialized class thì mới dùng được template specialization. => Nếu compiler chỉ nhìn thấy definition của bản non-specialized, nó sẽ dùng luôn bản đó thay vì bản specialization.
 

## Nested types

- Một nested class KHÔNG có quyền truy cập vào `this` pointer của outer class (class chứa nó). Tuy nhiên, nó CÓ THỂ truy cập mọi private members của outer class miễn là nằm trong scope:

    ```C++
    #include <string>
    #include <string_view>

    class Employee2
    {
    public:
        using IDType = int;     // Nested typedefs và type aliases

        class Printer   // Nested types
        {
        public:
            void print(const Employee2& e) const
            {
                // Printer không thể truy cập `this` pointer của Employee
                // nhưng có thể truy cập các private members e.m_name và e.m_id đang nằm trong scope
                std::cout << e.m_name << " has id: " << e.m_id << '\n';
            }
        };

    private:
        std::string m_name{};
        IDType m_id{};

    public:
        Employee2(std::string_view name, IDType id)
            : m_name{ name }
            , m_id{ id }
        {
        }
    };

    void func3()
    {
        const Employee2 john2{ "John", 1, 45000 };
        const Employee2::Printer p{}; // instantiate một object của inner class
        p.print(john2);
    }
    ```

## Destructor

* **Destructor**: là một class member function đặc biệt, được tự động gọi khi một object của class đó bị destroy (phá hủy). Ví dụ:
    * Khi một object rơi vào trạng thái out of scope một cách bình thường.
    * Khi một dynamically allocated object (object cấp phát động) bị xóa tường minh bằng từ khóa `delete`.
* Nếu constructor bị aborted (hủy ngang) vì bất kỳ lý do gì, destructor sẽ KHÔNG BAO GIỜ được gọi (do quá trình tạo object chưa hoàn tất).
* Quy tắc khai báo: Tên destructor bắt buộc phải giống hệt tên class, thêm dấu ngã (`~`) ở phía trước.
* Destructor KHÔNG nhận arguments.
* Destructor KHÔNG có return type.
* ⚠️ Lệnh `std::exit()` sẽ terminate (kết thúc) chương trình ngay lập tức, nhưng nó lại bỏ qua việc dọn dẹp các local variables => sẽ KHÔNG có destructor nào được gọi. Hết sức cẩn thận nếu hệ thống của bạn đang phụ thuộc vào destructor để thực hiện các tác vụ dọn dẹp quan trọng (như đóng file, giải phóng bộ nhớ, ghi log...).



## Static members

* Static member variables:
    * are shared by all objects of the class.
    * exists independently of any class objects.
    * are global variables that live inside the scope region of the class.
* ⚠️ You **must explicitly** define (and optionally initialize) the static member **outside** of the class, in the **global scope**.
    ```C++
    class Something
    {
    public:
        static int s_value; // declare
    };

    int Something::s_value{ 1 }; // define and initialize

    void func1()
    {
        Something::s_value = 2;
    }
    ```

    2 exceptions:
    * when the static member variables is a constant integral type or const enum, or
    * when the static member variables is inline. (Note: constexpr members variables are implicitly inline)
    ```C++
    class Whatever
    {
    public:
        static const int s_value1{ 4 }; // okay, constant integral type or const enum
        static inline int s_value2{ 4 }; // okay, inline
        static constexpr int s_value3{ 4 }; // okay, constexpr members are implicitly inline
    };
    ```
* If no initializer is provided, static member variables are zero-initialized by default.
* Static member function
    * can be useful when we need to access a **private** static member variable.
    * cannot directly access other non-static members.
    * have no `this` pointer.


## Friend

* A ***friend*** is a class or function (member or non-member) that has been granted full access to the private and protected members of another class.
* Friend non-member function:
    * ⚠️ A friend non-member function defined inside a class is treated as a non-member function.
* Friend classes:
    * class A is a friend of class B does not mean class B is also a friend of class A.
    * Nor is friendship inherited. If class A makes B a friend, classes derived from B are not friends of A.
    * A friend class declaration acts as a forward declaration for the class being friended. This means we do not need to forward declare the class being friended before friending it:

        ```C++
        class Storage
        {
        private:
            int m_nValue {};
        public:
            Storage(int nValue)
            : m_nValue { nValue }
            { }

            // Make the Display class a friend of Storage
            friend class Display;
        };

        class Display
        {
            // ...
        };
        ```
* Friend member functions: instead of making an entire class a friend, you can make a single member function a friend.


## Containers and arrays

* Array: 
    * a container data type that stores a sequence of values contiguously (in an adjacent memory location, with no gaps).
    * 3 primary C++ array types:
        * ⚠️ (C-style) arrays, behave strangely and they are dangerous.
        * `std::vector`, most flexible.
        * `std::array`: introduced in C++11 as a direct replacement for C-style arrays. More limited than `std::vector`, but can also be more efficient, especially for smaller arrays.
* Length and subscript problem:
    * ⚠️ when the container classes in the C++ standard library was being designed, the **length** and **subscripts** were decided to be **unsigned**. However, in retrospect, this is a wrong choice. Previously, we discussed the reasons why we prefer to use signed values to hold quantities.
* `std::vector`
    * is a template class.
        ```C++
        void passByRef(const std::vector<int>& arr) // we must explicitly specify <int> here
        {
            // ...
        }

        template <typename T>       // use a template
        void passByRef2(const std::vector<T>& arr)
        {
            // ...
        }
        ```
    * cannot be made constexpr.
    * ⚠️ The length and indices of `std::vector` have type `size_type`. `size_type` is almost always an alias for `std::size_t`. `std::size_t` is a typedef for some large unsigned integral type, usually `unsigned long` or `unsigned long long`.
        ```C++
        for (std::size_t index{ arr.size() - 1 }; index >= 0; --index) // index is unsigned
        ```
    * Under the hood, `std::vector` holds its elements in a C-style array. 👍  C-style arrays allow indexing with both signed and unsigned types (see: *Pointer arithmetic*).
    * Accessing array elements:
        * ⚠️ using operator[] does no bounds checking.
        * 👍 using the `.at()` member function does runtime bounds checking, but slower than operator[].
            ```C++
            std::vector<int> primes{ 2, 3, 5, 7 };

            std::cout << primes[9]; // undefined behavior
            std::cout << primes.at(9); // throws exception
            ```
        * 👍 Indexing with a constexpr signed int is not a narrowing conversion.
            ```C++
            constexpr int index { 3 };         // constexpr
            std::cout << primes[index] << '\n'; // okay, constexpr index implicitly converted to std::size_t, not a narrowing conversion
            ```
        * 👍 Indexing with a non-constexpr `std::size_t` value is not a narrowing conversion
            ```C++
            std::size_t index2 { 3 };           // non-constexpr of type std::size_t
            std::cout << primes[index2] << '\n'; // okay, no conversion required
        * ⚠️ Indexing with a non-constexpr signed value is a narrowing conversion.
            ```C++
            int index3 { 3 };                   // non-constexpr signed value
            std::cout << primes[index3] << '\n'; // possible warning: index implicitly converted to std::size_t, narrowing conversion
            ```
        * 👍 Indexing the result of the `.data()` member function with signed values is not a narrowing conversion.

             The `.data()` member function returns a pointer to the underlying C-style array => we don’t run into any sign conversion issues.

            ```C++
            int index3 { 3 };                   // non-constexpr signed value
            std::cout << primes.data()[index] << '\n'; // okay: no sign conversion warnings
            ```
    * `std::vector<bool>`:
        * ⚠️ It's not a real container and can breaks generic code. The C++ standard explicitly calls out `vector<bool>` as a special container where each bool uses only one bit of space rather than one byte as a normal bool would.
            * 👎️ => you can't take the address of a bit within a byte.
            * 👎️ => things such as operator[] can't return a bool&.
            * 👎️ => you can't assign its address to a bool* like you could with the other "normal" container.
            ```C++
            std::vector<bool> v_bool = {true, false, true};
            bool& ref = v_bool[0];  // error
            bool* ptr = &v_bool[0]; // error
            ```
        * Performance depends heavily on how well the implementation is optimized. Some implementations can be slower than alternatives.
* Fixed-size arrays vs dynamic arrays:
    * `std::array` and C-style arrays are fixed-size array types.
    * `std::vector` is a dynamic array.
    * **Length** vs **capacity**:
        * **capacity** is how many elements the std::vector has allocated storage for.
        * **length** is how many elements are currently being used.
        * A std::vector with a capacity of 5 has allocated space for 5 elements. If the vector contains 2 elements in active use, the length (size) of the vector is 2. The 3 remaining elements have memory allocated for them, but they are not considered to be in active use. They can be used later without overflowing the vector. (See syntax-and-snippnet for a demo).
    * Reallocation process:
        * When `std::vector` acquires new memory with capacity for the desired number of elements, these elements are **value-initialized**.
        * The elements in the old memory are copied (or moved, if possible) into the new memory. The old memory is then returned to the system.
        * The capacity and length of the std::vector are set to the new values.

        => ⚠️ Reallocation is an expensive process.
    * ⚠️ Resizing a vector changes both capacity and length:
        ```C++
        std::vector<int> arr2(3); // vector containing 3, the length is also being set to 3
        arr2.push_back(4);        // push on top of the stack
        for (auto i : arr2)
            std::cout << i << ' ';  // [0 0 0 4] instead of [4 0 0]

        std::vector arr3{1, 2, 3};
        arr3.resize(5);  // also changes the length
        arr3.push_back(4);
        for (auto i : arr3)
            std::cout << i << ' ';  // [1 2 3 0 0 4]
        ```
    * 👍 `reserve()` member function changes the capacity (but not the length):
        ```C++
        std::vector<int> arr4{};
        arr4.reserve(5);  // reserve 5 elements
        arr4.push_back(1);
        for (auto i : arr4)
            std::cout << i << ' ';  // [1]
        ```
    * `push_back()` vs `emplace_back()`:
        * Both push element to end of vector.
        * When we already have an object to be push, `push_back` and `emplace_back` are similar in efficiency.
        * However, in cases where we are creating a temporary object, `emplace_back` is more efficient:
        ```C++
        class Foo
        {
        public:
            Foo(int x, std::string b) {}
        };

        void func4()
        {
            std::vector<Foo> arr5;
            arr5.push_back({ 1, "a" }); // creates a temporary object, and then copies it into the vector
            arr5.emplace_back(1, "a");          // forwards the arguments so the object can be created directly in the vector (no copy made)
        }
        ```
* `std::array`:
    * When to use `std::array` over `std::vector`:
        * `std::vector` is slightly less performant than `std::array`.
        * (Main reason) `std::vector` only supports constexpr in very limited contexts.

            👎️ => Define `std::array` as constexpr whenever possible. If your `std::array` is not constexpr, consider using a `std::vector` instead.
    * the length of a `std::array` **must** be a constant expression.
        ```C++
        std::vector<int> b(7);    // a std::vector of 7 ints (for comparison)

        std::array<int, 7> arr2 {};  // using literal constant

        constexpr int len3 { 7 };
        std::array<int, len3> arr3 {};  // using constexpr variable
        ```
    * is an aggregate => to initialize it, we provide an initializer list.
        ```C++
        std::array<int, 5> arr5 { 1, 2, 3, 4, 5 };  // list initialization
        std::array<int, 5> arr6 = { 1, 2, 3, 4, 5 }; // copy-list initialization

        std::array<int, 5> arr7; // member default initialization (in most case left uninitialized)    
        std::array<int, 5> arr8 {}; // member value initialization (zero-initialized)

        std::array<int, 5> arr9 { 1, 2 }; // [1 2 0 0 0]

        // CTAD (C++17)
        constexpr std::array arr12 { 1, 2, 3}; // type is deduced to std::array<int, 3>
        ```
    * ⚠️ Aggregate initialization syntax works for `std::array`:
        ```C++
        struct House
        {
            int number{};
            int stories{};
            int roomsPerStory{};
        };

        void func1()
        {
            // work
            std::array<House, 3> houses{};
            houses[0] = { 13, 1, 7 };
            houses[1] = { 14, 2, 5 };
            houses[2] = { 15, 2, 4 };

            // work
            constexpr std::array houses2 { // CTAD to deduce <House, 3>
                House{ 13, 1, 7 },
                House{ 14, 2, 5 },
                House{ 15, 2, 4 }
            };

            // ⚠️ doesn't work
            constexpr std::array<House, 3> houses3 { 
                { 13, 1, 7 },
                { 14, 2, 5 },
                { 15, 2, 4 }
            };

            // works
            constexpr std::array<House, 3> houses4 {
                { // extra set of braces 
                    { 13, 4, 30 }, 
                    { 14, 3, 10 }, 
                    { 15, 3, 40 }, 
                }
            };
        }
        ```
        A `std::array` is defined as a "struct" like this:
        ```C++
        template<typename T, std::size_t N>
        struct array
        {
            T implementation_defined_name[N];
        }
        ```
        where `implementation_defined_name` is a C-style array with N elements of type T.

        => ⚠️ in the 3rd example, `{ 13, 1, 7 }` is used to initialize `implementation_defined_name`. Then the compiler will discover that we’ve provided two more initialization values (`{ 14, 2, 7 }` and `{ 15, 2, 5 }`) which exceeds the number of members in the struct.
    * Brace elision for `std::array`: 
        
        Given the explanation above, you may be wondering why the following single-brace syntax work?
        ```C++
        constexpr std::array<int, 3> arr { 1, 2, 3 }; // single braces
        constexpr std::array<int, 3> arr { { 1, 2, 3 } }; // double braces
        ```
        Generally, you can omit braces when initializing a `std::array` with:
        * scalar values, or
        * with class types where the type is explicitly named.

        👍 There is no harm in always initializing `std::array` with double braces.
    * Length and indexing of `std::array` is similar to `std::vector`. 👍 But, because the length of a `std::array` is constexpr, each of the `.size()`, `std::size()`, `.ssize()` (C++20) will return the length as a constexpr value (even when called on a non-constexpr std::array object)
        ```C++
        std::array<int, 5> arr13 { 1, 2, 3, 4, 5 }; // not constexpr
        constexpr int len13 { arr13.size() };  // ok, return value is constexpr std::size_t and can be converted to int, not a narrowing conversion
        ```
    * While 👎️ `operator[]` does no bounds checking and 👎️ `at()` member function 
  only does runtime bounds checking (remind that function parameters can’t be constexpr), 👍 the `std::get()` function template does compile-time bounds checking.

        ```C++
        constexpr std::array<int, 5> arr14 { 1, 2, 3, 4, 5 };
        std::cout << std::get<2>(arr14) << '\n';  // 3
        std::cout << std::get<10>(arr14) << '\n';  // compile-time error
        ```
    * ⚠️ Pass `std::array` by (const) reference: the type of the non-type template parameter for std::array should be `std::size_t`, not `int`. 
        ```C++
        void passByRef(const std::array<int, 5>& arr) // we must explicitly specify <int, 5> here
        {
            // ...
        }

        template <typename T, std::size_t N>
        void passByRef2(const std::array<T, N>& arr)
        {
            // ...
        }
        ```
    * ⚠️ Returning a `std::array`: Unlike `std::vector`, `std::array` is not move-capable, so **returning it by value** will make a copy => Consider using an out parameter or use `std::vector` instead.
* Arrays of references:
    * ⚠️ You **cannot** make an array of references. Because, the elements of an array must be assignable, while references can’t be reseated.
        ```C++
        int x { 1 };
        int y { 2 };
        std::array<int&, 2> refarr { x, y }; // compile error

        int& ref1 { x };
        int& ref2 { y };
        std::array valarr { ref1, ref2 }; // ok, but this is actually a std::array<int, 2>, not an array of references
        valarr[0] = 10;
        std::cout << valarr[0] << " " << x << '\n'; // 10 1
        ```
    * 👍 `std::reference_wrapper` behaves like a modifiable lvalue reference to T:
        ```C++
        std::array<std::reference_wrapper<int>, 2> arr { x, y };
        arr[0].get() = 10;
        std::cout << arr[0] << " " << x << '\n'; // 10 10
        ```

        Notes about `std::reference_wrapper`:
        * `Operator=` will "reseat" a `std::reference_wrapper`.
        * `std::reference_wrapper<T>` will implicitly convert to `T&`.
        * `get()` member function can be used to get a `T&`.
* C-style array:
    * Syntax: use square brackets (`[]`) to declare a C-style array:
        ```C++
        int arr[5]; // define an array of 5 int values
        ```
    * The length of a C-style array **must** be a constant expression of type `std::size_t` (Just like `std::array`).
    * CTAD doesn’t work with C-style array, so we must explicitly specified element's type.
        ```C++
        auto arr7[5] { 1, 2, 3, 4, 5 }; // compile error
        ```
    * C-style arrays are aggregates (Just like `std::array`) => they can be initialized using aggregate initialization.
    * When we initialize a C-style array with an initializer list, we can omit the length:
        ```C++
        int arr8[] { 1, 2, 3, 4, 5 }; // the length is deduced
        ```
    * Getting the length of a C-style array:
        * (C++17) can use `std::size()` or `std::ssize()`.
        * ⚠️ Prior to C++17, there was no standard library function to get the length of a C-style array => we can use this function instead:
            ```C++
            template <typename T, std::size_t N>
            constexpr std::size_t length(const T(&)[N]) noexcept
            {
                return N;
            }

            int arr[5];
            std::cout << length(arr) << '\n'; // prior to C++17
            std::cout << std::size(arr) << '\n'; // C++17, returns unsigned integral
            std::cout << std::ssize(arr) << '\n'; // C++20, returns signed integral
            ```
    * C-style arrays don’t support assignment:
        ```C++
        int arr9[3] { 1, 2, 3 };
        arr9[0] = 4; // ok
        arr9 = { 4, 5, 6 }; // compile error
        ```
    * C-style array decay:
        * In most cases, when a C-style array is used in an expression, the array will be implicitly converted into a pointer, initialized with the address of the first element (with index 0).
            ```C++
            int arr1[] { 1, 2, 3, 4, 5 };   // array
            auto ptr{ arr1 }; // decayed array. Type deduction should deduce type int*
            std::cout << std::boolalpha << (typeid(ptr) == typeid(int*)) << '\n'; // true
            std::cout << std::boolalpha << (&arr1[0] == ptr) << '\n'; // true

            ```
        * Cases in C++ where an C-style array doesn’t decay:
            * When used as an argument to `sizeof()` or `typeid()`.
            * When taking the address of the array using `operator&`.
            * When passed as a member of a class type.
            * When passed by reference.
        * 👍 => avoid expensive copy
        * 👍 => a single function can accept arrays of different sizes
            ```C++
            void f(const int* arr) // pass by const address
            {
                // ...
            }

            int arr1[] { 1, 2, 3, 4, 5 };
            f(arr1);
            ```
        * Syntax:
            * 👎️ declaring the function parameter as `int* arr` makes it not obvious that `arr` is a "pointer to an array" rather than a pointer to a single integer.
            * 👎️ declaring the function parameter as `int arr[]` is more preferred, but makes it less obvious that `arr` has decayed

            ```C++
            void f(const int arr[]) // pass by const address
            {
                // ...
            }
            ```
        * ⚠️ Problems: Loss of length information. Consequence:
            * `sizeof()` will return different values for arrays and decayed arrays:
                ```C++
                void printArraySize(int arr[])
                {
                    std::cout << sizeof(arr) << '\n'; // prints 4 (assuming 32-bit addresses)
                }

                int arr1[] { 1, 2, 3, 4, 5 };
                std::cout << sizeof(arr1) << '\n'; // prints 20 (assuming 32-bit addresses)
                ```
            * make refactoring difficult
            * Some work-arounds:
                * pass the length of the array as a separate parameter.
                    * 👎️ sign conversion issues
                    * 👎️ cannot do compile-time validation
                    * 👎️ only work with explicit call. If the array is passed as operand, we cannot pass in the length.
                * mark the end of the array using a special element.
                    * 👎️ need special handling for the terminating element.
                    * 👎️ mismatch between the array actual length and the number of semantically valid elements.
    * C-style string: 
        * simply declare a C-style array variable of `char`:
            ```C++
            char str1[8]{};                    // 8 char, including hidden null-terminator character
            const char str2[]{ "string" };     // 7 char, including hidden null-terminator character
            ```
        * Outputting: `std::cout` outputs characters until it encounters the null terminator. `std::cout` makes some assumptions:
            * If you pass it a non-char **pointer**, it will simply print the contents of that pointer.
            * If you pass it an object of type `char*` or `const char*`, it will print a string.
            ```C++
            const char str2[]{ "string" };
            std::cout << str2 << '\n'; // string

            int narr[]{ 9, 7, 5, 3, 1 };
            std::cout << narr << '\n'; // 0x7ffeeb1b3b40

            char c{ 'Q' };
            std::cout << &c << '\n'; // undefined behavior
            // intending to print the address of c. However, &c has type char*, so std::cout will try to print this as a string.
            // But, because c is not null-terminated, we get undefined behavior.
            ```
        * Inputting:
            * ⚠️ Prior to C++20, `std::cin` would extract as many charaters as possible (stopping at the first non-leading whitespace) => might overflow.
            * In C++20, `operator>>` only work for inputing non-decayed C-style strings => extract only as many characters as length will allow
            * *See syntax-and-snippnet for the the recommended way to read C-style strings.*
        * ⚠️ Getting the length:
            * `std::size()` or `std::ssize()` returns the actual length of the array, not the length of the string => use `strlen()`
            * But `strlen()` is slow, as it has to traverse through the array to count until it hits the null terminator.
        * C-style string symbolic constants:
            ```C++
            const char name[] { "Alex" };     // case 1: const C-style string initialized with C-style string literal
            const char* const color{ "Orange" };    // case 2: const pointer to C-style string literal
            ```
            While producing the same results, the memory allocation for the 2 methods behave differently:
            * Case 1:
                * “Alex” is put into (probably read-only) memory somewhere.
                * program allocates memory for a C-style array of length 5 and initializes it with “Alex"

                => 2 copies of “Alex”.
            * Case 2:
                * places the string “Orange” into read-only memory somewhere.
                * initializes the pointer with the address of the string.
* Multidimensional arrays: *see code in github lesson*.
* Iterate through an array: Different ways:
    * using indexes
    * using *Pointer arithmetic*:
        * All standard library containers offer direct support for iteration:
            * using member functions `begin()` and `end()`
            * or, using functions `std::begin` and `std::end`

        ```C++
        template <typename T>
        void print(const T* begin, const T* end)
        {
            for (auto p{ begin }; p != end; ++p) // ++ to move to next element.
            {
                std::cout << *p << ' '; // Indirection to get value of current element.
            }
        }

        std::array array{ 1, 2, 3 };

        auto begin{ array.begin() };
        auto end{ array.end() };
        print(begin, end);

        auto begin2{ std::begin(array) };
        auto end2{ std::end(array) };
        print(begin2, end2);
        ```

        ```C++
        void printArray(const int* begin, const int* end)
        {
            for (; begin != end; ++begin)   // iterate from begin up to (but excluding) end
            {
                std::cout << *begin << ' '; // dereference our loop variable to get the current element
            }
        }

        constexpr int arr[]{ 9, 7, 5, 3, 1 };

        const int* begin{ arr };                // begin points to start element
        const int* end{ arr + std::size(arr) }; // end points to one-past-the-end element

        printArray(begin, end);
        ```
        * ⚠️ Much like pointers and references, iterators can be left “dangling” if the elements being iterated over change address or are destroyed.
    * Range-based for-loops: They use iterators.
        ```C++
        template <typename T>
        void print(const std::vector<T>& arr)
        {
            for (auto num : arr) // iterate and copy each value into `num`
            {
                // ...
            }
        }
        ```
        * Work with a wide variety of array types, including non-decayed C-style arrays, std::array, std::vector, linked list, trees, and maps.
        * The loop variable should have the same type as the array elements => prefer using `auto`
        * ⚠️ Elements are copied to the loop variable 
            * Expensive for some types => ✅ can use reference to avoid such copy.
            * Cannot change the values in the array => ✅ can use non-const reference.
            ```C++
            for (const auto& num : arr) // if non-const, the reference can change the values in the array
            {
                // ...
            }
            ```
        * Loops in reverse (C++20):
            ```C++
            #include <ranges> // C++20
            for (const auto& num : std::views::reverse(arr))
            {
                // ...
            }
            ```
        * Behind the scenes, the range-based for-loop calls `begin()` and `end()` of the type to iterate over.

* `std::initializer_list`:
    * Consider initialization using initializer lists syntax:
    ```C++
    int array[] { 5, 4, 3, 2, 1 };
    ```
    When a compiler sees an initializer list, it automatically converts it into an object of type std::initializer_list.
    
    => ✅ Therefore, if we create a constructor that takes a `std::initializer_list` parameter, we can create objects using the initializer list as an input.

    ```C++
    class Element
    {
    private:
        int m_value{};
    public:
        Element(int value) : m_value{ value } {}
    };

    class MyArray
    {
    public:
        // ...

        MyArray(std::initializer_list<Element> list) // allow MyArray to be initialized via list initialization
        {
            // ...
        }

        // ...
    };


    MyArray array{ Element{1}, Element{2}, Element{3}}; // initializer list
    ```
    * It has a `size()` member function which returns the number of elements in the list.
    * Much like `std::string_view`, `std::initializer_list` is a view. 
        * ✅ => `std::initializer_list` is often passed by value
        * ⚠️ => Copying a `std::initializer_list` does not copy the elements in the list.


## C-style string, `std::string`, `std::string_view`

* `std::string` và `std::string_view` không phải là fundamental type (chúng là các class type).
* `std::string_view` read-only đến một string sẵn có mà không tạo copy.
* C-style string và `std::string` đều có thể tự động ép kiểu (implicitly convert) sang `std::string_view`. Nhưng `std::string_view` không implicitly convert thành `std::string`.
* `std::string` là chủ sở hữu duy nhất của dữ liệu, còn `std::string_view` chỉ là một viewer.
* Các string literal:
    * `"Hello, world!"`: C-style string literal
    * `"Hello, world!"s`: `std::string` literal
    * `"Hello, world!"sv`: `std::string_view` literal.


## Command line arguments

* `argc`: the number of arguments passed to the program, always be at least 1.
* `argv`: C-style array of char pointers (the length of this array is `argc`), each of which points to a C-style string.
* To use a command line argument as a number, you must convert it from a string to a number. (See syntax-and-snippnet).


## Ellipsis

* 👍 Ellipsis allows us to pass a **variable** number of parameters to a function. (See code in github lesson). 


## Lambdas

* **Functors** are objects that contain an overloaded `operator()` that make them callable.
* **Lambdas** are a special kind of functor.
* ✅ Lambdas aren’t functions, which is part of how they avoid the limitation of C++ not supporting nested functions.
* Lambdas can have no name if we defined a it right where it was needed. This use is called a **function literal**:
    ```C++
    int x{ 7 };
    int y{};
    y = [](int a) -> int { return a * 2; }(x);  // y = 14
    ```
* (C++14) Lamdas’re allowed to use `auto` for parameters. A unique lambda will be generated for each different type that `auto` resolves to.
* In lambda, static variables work exactly the same as regular functions.
* (C++17) Lambdas are implicitly constexpr if:
    1. They have no captures, or all captures must be constexpr.
    2. Functions called by the lambda must be constexpr.
* Lambda **captures**:
    * 👎️ Unlike nested blocks, where any identifier accessible in the outer block is accessible in the nested block. Lambdas can only access objects defined outside the lambda if:
        * they have static (or thread local) storage duration (e.g., global variables and static locals)
        * or, they are constexpr (explicitly or implicitly)
        * or, they are listed in **capture clause**.
    * ⚠️ The captured variables of a lambda are **copies** of the outer scope variables.
        ```C++
        int y{ 5 };
        [y]() { } ();  // y is cloned
        ```
    * ⚠️ 
        * At **compile** time, when the compiler encounters a lambda definition, it creates a custom object definition for the lambda. Each captured variable becomes a data member of the object.
        * At runtime, when the lambda definition is encountered, the lambda object is instantiated. The members of the lambda are initialized at that point and ⚠️ persisted across multiple calls to the lambda!
    * Captures are const by default:
        ```C++
        [y]() { ++y } (); // error, inside the lambda, y is const.
        ```
    * *Mutable* captures:
        ```C++
        int y{ 5 };

        auto increment {[y]() mutable
        {
            ++y;
            std::cout << y << '\n';
        }};
        increment();    // 6, y is modified inside the lambda. But it's a copy of the outer y.
        increment();    // 7, y is persisted across multiple calls to the lambda

        std::cout << y << '\n'; // 5, y is not modified outside the lambda.
        ```
    * Capture by reference
        ```C++
        int y{ 5 };
        [&y]() { ++y; } ();
        std::cout << y << '\n'; // 6, y is modified.
        ```
    * Multiple captured variables: 
        * This can include a mix of variables captured by value or by reference
            ```C++
            [x, &y]() { } ();
            ```
        * **Default captures** capture all variables.
            * To capture all variables by value, use `=`.
            * To capture all variables by reference, use `&`.
            * can be mixed with normal captures.

            ```C++
            int a{ 1 }, b{ 2 }, c{ 3 };
            auto d{ [=]() { return a + b + c; } () };   // a, b, c are captured by value.            
            auto e{ [&, a, b]() { return a + b + c; } () };   // a, b are captured by value, c is captured by reference.
    * Defining new variables in the lambda-capture:
        * The newly defined variable is the same for every call. But if a lambda is "mutable" and modifies a variable that was defined in the capture, the original value will be overridden.
            ```C++
            int x{ 2 };
            int y{ 5 };

            auto f { [new_var{ x * y }]() mutable { new_var++; } };
            
            f();    // new_var is 11
            f();    // new_var is 12
    * ⚠️ Dangling captured variables
        ```C++
        // returns a lambda
        auto print1(const std::string& name)
        {
            return [&]() {          // Capture name by reference
                std::cout << name;  // Undefined behavior
            };
        }

        auto print2(const std::string& name)
        {
            return [=]() {          // Capture name by value
                std::cout << name;
            };
        }

        auto printWilly1{ print1("Willy") }; // the temporary string literal "Willy" dies at the end of this command
        printWilly1(); // `name` is a dangling reference 
        auto printWilly2{ print1("Willy") };
        printWilly2(); // okay
        ```


## Overloading operators

* 3 different ways:
    1. Using friend functions
    2. Using normal functions
    3. Using member functions
* Overload io operators: (See code in github lesson)
* Overload subscript operator: (See code in github lesson)
* Overload typecast: (See code in github lesson)
    * Overloaded typecasts and converting constructors perform similar roles.
    * In general, a converting constructor should be preferred, as it allows the type being constructed to own the construction.
    * There are a few cases where an overloaded typecast should be used instead:
        1. When providing a conversion to a fundamental type or a type you can’t add members to (since you can’t define constructors for these types).
        2. When avoiding circular dependencies.
* Overload assignment operator: (See code in github lesson and below)


## Memory allocation

* Tổng quan về memory:
    * Memory mà chương trình sử dụng thường được chia thành các vùng (areas), gọi là các ***segments***:
        * **code segment** (hay text segment): Lưu trữ compiled program (mã lệnh đã biên dịch).
        * **bss segment** (uninitialized data segment): Lưu trữ các global và static variables được zero-initialized.
        * **data segment** (initialized data segment): Lưu trữ các global và static variables đã được khởi tạo giá trị.
        * **heap**: Lưu trữ các dynamically allocated variables (biến cấp phát động).
        * **call stack**: Lưu trữ function parameters, local variables và các thông tin quản lý function khác.
* **Call stack**:
    * Khi chương trình chạy đến một function call:
        1. Một **stack frame** được tạo ra và push vào stack. Stack frame chứa:
            * **Return address** (địa chỉ của instruction ngay sau function call) => cho biết CPU cần nhảy về đâu sau khi function chạy xong.
            * Toàn bộ function arguments.
            * Memory dành cho các local variables.
            * Bản sao lưu của các registers (thanh ghi) bị function thay đổi, dùng để restore lại khi function return.
        2. CPU jump tới điểm bắt đầu của function.
        3. Các instructions bên trong function bắt đầu được execute (thực thi).
    * Khi function kết thúc (terminates):
        1. Các registers được restore từ call stack.
        2. Stack frame được pop khỏi stack. Bước này sẽ free (giải phóng) memory của toàn bộ local variables và arguments.
        3. Xử lý return value.
        4. CPU tiếp tục execute từ vị trí return address.
    * Toàn bộ memory cấp phát trên stack đều được xác định rõ kích thước từ lúc **compile time**. Do đó, ta có thể access trực tiếp vào memory này thông qua variable.
    * ⚠️ **Stack overflow**:
        * Stack có giới hạn dung lượng khá nhỏ (VD: mặc định 1MB trên Visual Studio, 8MB với g++/Clang trên Unix).
        * Lỗi stack overflow thường xảy ra do cấp phát memory cho variables quá lớn hoặc gọi nested function (hàm lồng nhau/đệ quy) quá sâu trên stack.
        
        ```C++
        int stack[10000000];
        std::cout << "hi" << stack[0];
        // Segmentation fault, do cố gắng cấp phát một array khổng lồ (tầm 40MB) ngay trên stack
        ```
* C++ hỗ trợ 3 loại memory allocation cơ bản:
    * **Static** memory allocation: dùng cho static và global variables.
        * Chỉ cấp phát 1 lần duy nhất khi chạy chương trình, và tồn tại suốt vòng đời của chương trình.
    * **Automatic** memory allocation: dùng cho function parameters và local variables.
        * Được cấp phát khi đi vào block tương ứng, và được free (giải phóng) khi thoát khỏi block.

        Điểm chung của static và automatic allocation:
            * Kích thước variable phải được xác định rõ từ lúc compile time.
            * 👍 Quá trình allocation và deallocation diễn ra hoàn toàn **tự động**.
            * Hầu hết các variables thông thường được cấp phát trên **stack** memory (dung lượng khá nhỏ).
    * **Dynamic** memory allocation:
        * Là cách request memory từ OS khi cần thiết (lúc runtime).
        * ⚠️ Lập trình viên phải tự tay dispose (giải phóng) memory đã cấp phát.
        * Sử dụng **heap** memory (thường chậm hơn stack memory).
* Dynamic memory allocation:
    * Cấp phát biến đơn ("single" variables):
        ```C++
        int* ptr{ new int };    // dynamically allocate một số nguyên và gán địa chỉ cho ptr
        delete ptr;     // trả lại memory cho OS
        ptr = nullptr;

        // dynamically allocate và khởi tạo (initialize)
        int* ptr1{ new int (5) };   // direct initialization
        int* ptr2{ new int { 6 } }; // uniform initialization
        delete ptr1;
        ptr1 = nullptr;
        delete ptr2;
        ptr2 = nullptr;
        ```
    * Cấp phát arrays (demo bằng C-style arrays):
        ```C++
        std::size_t length{ 10 };   // không bắt buộc phải là constexpr
        int* array{ new int[length]{} }; 
        delete[] array;

        // dynamically allocate và khởi tạo
        int* array2{ new int[5]{ 9, 7, 5, 3, 1 } };
        auto* array3{ new int[5]{ 9, 7, 5, 3, 1 } };    // type deduction
        int* array4{ new int[]{ 9, 7, 5, 3, 1 } };      // Không bắt buộc phải ghi rõ size của array.
        delete[] array2;
        delete[] array3;
        delete[] array4;
        ```
    * ⚠️ Deallocate memory có thể vô tình tạo ra nhiều dangling pointers:
        ```C++
        int* ptr3{ new int{} };
        int* otherPtr{ ptr3 }; // otherPtr lúc này trỏ tới cùng một địa chỉ memory với ptr3
        delete ptr3; // vùng nhớ bị xóa => ptr3 và otherPtr giờ đều trở thành dangling pointers.
        ptr3 = nullptr;
        // tuy nhiên, otherPtr vẫn đang là một dangling pointer!
        ```
    * ⚠️ Quá trình allocate có thể thất bại: Trong vài trường hợp hiếm, OS không còn memory để cấp phát. Mặc định, một exception `bad_alloc` sẽ bị throw và chương trình sẽ crash. ✅ Để tránh điều này, ta có thể yêu cầu trả về null pointer (thay vì crash) bằng cách thêm `std::nothrow`:
        ```C++
        int* value { new (std::nothrow) int };
        ```
    * Thực chất khi gọi `delete ptr`, ta không xóa biến `ptr`. Biến này vẫn tồn tại và có thể được gán một giá trị mới (VD: `nullptr`) giống như bất kỳ variable nào khác.
    * ⚠️ **Memory leaks**: Xảy ra khi chương trình làm mất địa chỉ memory trước khi kịp trả nó về cho OS => OS sẽ vĩnh viễn không thể sử dụng lại vùng memory đó nữa.
        ```C++
        {
            int* ptr{ new int{} };
        } // ptr rơi vào out of scope, ta mất luôn địa chỉ của vùng nhớ vừa allocate => memory leak

        {
            int value = 5;
            int* ptr{ new int{} }; // allocate memory
            ptr = &value; // gán con trỏ sang địa chỉ mới => mất địa chỉ memory cũ => memory leak
        }
        ```

        ```C++
        void func1()
        {
            int* ptr = new int;

            return; // hàm return sớm, ptr chưa kịp delete!

            delete ptr;
        } // => memory leak
        
        => ✅ Giải pháp: Xem phần **smart pointer**.
        ```


## Copy constructors and Copy assignment

* **Copy constructor**:
    * It's a constructor that is used to initialize an object with an existing object of the same type. The copy constructor’s parameter must be a **reference**.

        ```C++
        class Fraction2
        {
        private:
            int m_numerator{ 0 };
            int m_denominator{ 1 };

        public:
            Fraction2(int numerator=0, int denominator=1)
                : m_numerator{numerator}, m_denominator{denominator}
            {
            }

            // Copy constructor
            Fraction2(const Fraction2& fraction)
                : m_numerator{ fraction.m_numerator }
                , m_denominator{ fraction.m_denominator }
            {
            }
        };
        ```
    * **Implicit copy constructor**: 
        * If you do not provide a copy constructor for your classes, C++ will create a public implicit copy constructor. 
        * By default, the implicit copy constructor will do memberwise initialization.

            ```C++
            class Fraction
            {
            private:
                int m_numerator{ 0 };
                int m_denominator{ 1 };

            public:
                // Default constructor
                Fraction(int numerator=0, int denominator=1)
                    : m_numerator{numerator}, m_denominator{denominator}
                {
                }
            };

            void func1()
            {
                Fraction f { 5, 3 };
                Fraction fCopy { f }; // => implicit copy constructor
            }
            ```
    * **Pass by value**, **return by value**, **initialization** of the same class type will implicitly invoke the copy constructor:

        ```C++
        void printFraction(Fraction2 f) // f is pass by value
        {
        }

        void func2()
        {
            Fraction2 f2 { 5, 3 };
            printFraction(f2); // f is copied using copy constructor

        }
        ```

        ```C++
        Fraction2 generateFraction(int n, int d)
        {
            return Fraction2{ n, d };
        }

        void func3()
        {
            Fraction2 f3 { generateFraction(5, 3) }; // 2 copy constructors are called here, one for the return value and one for the initialization of f3
        }
        ```
    * **Copy elision**: the compiler can optimize away the unnecessary copy constructor calls. We say the constructor has been **elided**.
* **Copy assignment**:
    * Overloading `operator=` is fairly straightforward, with one specific caveat:
        ```C++
        class Fraction
        {
        private:
            int m_num { 0 };
            int m_den { 1 };
        public:
            Fraction(int num = 0, int den = 1)
                : m_num{ num }, m_den{ den }
            { }

            // Overload assignment operator (don't use this version in real code. See Self-assignment)
            Fraction& operator=(const Fraction& other)
            {
                m_num = other.m_num;
                m_den = other.m_den;

                return *this;
            }
        };

        Fraction a{ 1, 2 };
        Fraction b{ 3, 4 };

        a = b; // uses overloaded assignment operator
        a = a; // self-assignment
        ```
    * ⚠️ Self-assignment: In most cases, self-assignment has no overall impact, other than wasting time. However, it can actually be dangerous if it needs to handle dynamic memory:
        ```C++
        class MyArray
        {
        private:
            int* m_data {};
            int m_len {};

        public:
            MyArray(const int* data = nullptr, int len = 0 )
                : m_len { len }
            {
                m_data = new int[static_cast<std::size_t>(len)];
                std::copy_n(data, len, m_data); // copy len elements of data into m_data
            }
            ~MyArray()
            {
                delete[] m_data;
            }

            // Overloaded assignment    (don't use this version)
            MyArray& operator= (const MyArray& str)
            {
                // if data exists in the current string, delete it
                if (m_data) delete[] m_data;        // m_data will be dangling if self-assignment occurs

                m_len = str.m_len;
                m_data = nullptr;

                m_data = new int[static_cast<std::size_t>(str.m_len)];

                std::copy_n(str.m_data, m_len, m_data);

                return *this;
            }
        };

        MyArray alex("Alex", 5);
        alex = alex;        // self-assignment
        ```

        ✅ Simply add a **self-assignment guard** at the start of your assignment operator:
        ```C++
        MyString& MyString::operator= (const MyString& str)
        {
            if (this == &str)
                return *this;
            
            // ...
        }
        ```
    * **Implicit** copy assignment operator:
        * ⚠️ Unlike other operators, the compiler will provide an implicit `operator=` if you do not provide a user-defined one.
        * You can prevent assignments by making it private or using the `delete` keyword.
        * If your class has const members, the compiler will define the implicit `operator=` as deleted. If you that class to be assignable (for all members that aren’t const), you will need to explicitly overload `operator=`.


## Shallow copy and deep copy

* The default copy constructor and default assignment operators use **shallow copy**. When classes are simple, this works very well. ⚠️ However, if it handles dynamically allocated memory, shallow copy just copies the address of the pointer:
    ```C++
    class MyString
    {
    private:
        char* m_data{}; // pointer to a dynamically allocated array
        int m_length{};

    public:
        MyString(const char* source = "")
        {
            assert(source); // make sure source isn't a null string

            m_length = std::strlen(source) + 1;
            m_data = new char[m_length];

            for (int i{ 0 }; i < m_length; ++i)
                m_data[i] = source[i];
        }

        ~MyString() { delete[] m_data; }
    };

    MyString hello{ "Hello, world!" };
    {
        MyString copy{ hello }; // shallow copy, use default copy constructor
    } // `copy` gets destroyed here => make `hello` with a dangling pointer
    ```
* **Deep copy** requires that we write our own copy constructors and overloaded assignment operators:
    ```C++
    class MyString2
    {
    private:
        char* m_data{}; // pointer to a dynamically allocated array
        int m_length{};

    public:
        MyString2(const char* source = "" )
        {
            // ... same as above
        }

        ~MyString2() { delete[] m_data; }

        MyString2(const MyString2& source);
        MyString2& operator=(const MyString2& source);
        void deepCopy(const MyString2& source);
    };

    void MyString2::deepCopy(const MyString2& source)
    {
        // deallocate first
        delete[] m_data;

        m_length = source.m_length;

        // if m_data is non-null
        if (source.m_data)
        {
            m_data = new char[m_length];
            for (int i{ 0 }; i < m_length; ++i)
                m_data[i] = source.m_data[i];
        }
        else
            m_data = nullptr;
    }

    MyString2::MyString2(const MyString2& source) { deepCopy(source); }

    MyString2& MyString2::operator=(const MyString2& source)
    {
        if (this == &source)    // self-assignment guard
            return *this;

        deepCopy(source);
        return *this;
    }

    MyString2 hello2{ "Hello, world!" };
    {
        MyString2 copy{ hello2 };
    } // `copy` gets destroyed here => `hello2` is still valid
    ```
* ✅ Classes in the standard library (such as `std::string` and `std::vector`) do proper deep copying.
* ⚠️ **Rule of Three**: If your class needs any of
    1. a copy constructor,
    2. a assignment operator,
    3. a destructor,
    defined explictly, then it is likely to need **all three** of them, or you should delete the copy constructor.

    Consider the following code:
    ```C++
    class IntArray2
    {
    private:
        int m_length{};
        int* m_data{};

    public:
        IntArray2() = default;

        IntArray2(int length)
            : m_length{ length }
            , m_data{ new int[static_cast<std::size_t>(length)] {} }
        {

        }

        IntArray2(std::initializer_list<int> list)
            : IntArray2(static_cast<int>(list.size()))
        {
            std::copy(list.begin(), list.end(), m_data);
        }

        ~IntArray2()
        {
            delete[] m_data;
        }

    //	IntArray2(const IntArray2&) = delete; // to avoid shallow copies
    //	IntArray2& operator=(const IntArray2& list) = delete; // to avoid shallow copies

        int& operator[](int index)
        {
            assert(index >= 0 && index < m_length);
            return m_data[index];
        }

        int getLength() const { return m_length; }
    };

    void func2()
    {
        IntArray2 array{};
        array = { 1, 3, 5, 7, 9, 11 }; // assignment

        for (int count{ 0 }; count < array.getLength(); ++count)
            std::cout << array[count] << ' '; // undefined behavior
    }
    ```
    ⚠️ Here is what happens:
    1. the compiler sees that an assignment function taking a `std::initializer_list` doesn’t exist.
    2. Then, it discovers the **implicit** copy assignment operator. However, this function can only be used if it can convert the initializer list into an IntArray.
    3. The compiler realizes that `{ 1, 3, 5, 7, 9, 11 }` is a `std::initializer_list`, which can be converted to a temporary `IntArray` using list constructor.
    4. Then, the implicit copy assignment operator will do shallow copy.
    5. Finally, the temporary `IntArray` is destroyed, leaving `array->m_data` as a dangling pointer.


## Move constructors and move assignment

* Copy semantics and Move semantics:
    * **Copy semantics**:
        * refers to how copies of objects are made.
        * For class types, copy semantics are typically implemented via the copy constructor and copy assignment operator.
    * **Move semantics**:
        * determine how the data from one object is moved (transfer ownership) to another object.
        * 👍 When move semantics is invoked, any data member that can be moved is moved, and any data member that can’t be moved is copied. => more efficient than copy semantics
* Copy semantics:
    ```C++
    class Resource
    {
    public:
        Resource() { std::cout << "Resource acquired\n"; }
        ~Resource() { std::cout << "Resource destroyed\n"; }
    };

    template <typename T>
    class MyClass
    {
        T* m_ptr {};
    public:
        MyClass(T* ptr=nullptr)
            :m_ptr(ptr)
        { }

        ~MyClass() { delete m_ptr; }

        // Copy constructor
        MyClass(const MyClass& a)
        {
            m_ptr = new T;
            *m_ptr = *a.m_ptr;		// use assignment to copy the value
        }

        // Copy assignment
        MyClass& operator=(const MyClass& a)
        {
            // Self-assignment detection
            if (&a == this)
                return *this;

            delete m_ptr;

            m_ptr = new T;
            *m_ptr = *a.m_ptr;

            return *this;
        }
    };

    MyClass<Resource> generateResource()
    {
        MyClass<Resource> res{new Resource};
        return res; // this return value will invoke the copy constructor
    }

    MyClass<Resource> mainres;
    mainres = generateResource(); // this assignment will invoke the copy assignment
    ```
    Here is what happens:
    1. `res` is constructed in `generateResource()` => Resource acquired
    2. When `res` is returned by value, it's copy constructed to a temporary object => Resource acquired
    3. `res` is destroyed => Resource destroyed
    4. The temporary object is copy assigned to `mainres` => Resource acquired
    5. The temporary object is destroyed => Resource destroyed
    6. `mainres` is destroyed => Resource destroyed 
    
    => 👎️ unnecessarily expensive copying
* Move semantics:
    * while the copy constructors/assignment take a **const l-value reference** parameter, the move constructors/assignment use **non-const rvalue reference** parameters:
    ```C++
    template<typename T>
    class MyClass
    {
        // ...

        // Move constructor
        MyClass(MyClass&& a) noexcept
            : m_ptr(a.m_ptr)
        {
            a.m_ptr = nullptr;	// don't forget
        }

        // Move assignment
        MyClass& operator=(MyClass&& a) noexcept
        {
            // Self-assignment detection
            if (&a == this)
                return *this;

            delete m_ptr;

            m_ptr = a.m_ptr;
            a.m_ptr = nullptr;	// don't forget

            return *this;
        }
    };

    // ...
    ```
    Here is what happens:
    1. `res` is constructed in `generateResource()` => Resource acquired
    2. When `res` is returned by value, it's move constructed to a temporary object, then `res` is destroyed.
    3. The temporary object is move assigned to `mainres`, then the temporary object is destroyed.
    4. `mainres` is destroyed => Resource destroyed

* ⚠️ Normally, when an object is being initialized with (or assigned) an object of the **same type**, copy semantics will be used (assuming the copy isn’t elided). However, when all of the following are true, move semantics will be invoked instead:
    1. The type of the object supports move semantics.
    2. The object is being initialized/assigned with an rvalue object of the same type.
    3. The move isn’t elided.

* ✅ For move-capable types, move semantics might be invoked **automatically** when **returning by value** from a function, even if the returned object is an l-value.

    Both `std::vector` and `std::string` support move semantics => it is okay to return them by value!!!
* **Implicit** move constructor/assignment: ... if all of the following are true:
    1. There are no user-declared copy constructors/assignment.
    2. There are no user-declared move constructors/assignment.
    3. There is no user-declared destructor.

    These move functions will do a member-wise move as follows:
    * If member has a move constructor or move assignment (as appropriate), it will be invoked.
    * Otherwise, the member will be copied.

    ⚠️ This means that implicit constructor/assignment will copy pointers, not move them! If you want to move a pointer member, you will need to define the move constructor and move assignment yourself.

* ✅ `std::move`:
    * a function that casts (using `static_cast`) its argument into an r-value reference, so that move semantics can be invoked
        ```C++
        template <typename T>
        void mySwapCopy(T& a, T& b)
        {
            T tmp { a }; // invokes copy constructor because a is an l-value
            a = b; // invokes copy assignment because b is an l-value
            b = tmp; // invokes copy assignment because tmp is an l-value
        }

        template <typename T>
        void mySwapMove(T& a, T& b)
        {
            T tmp { std::move(a) }; // invokes move constructor
            a = std::move(b); // invokes move assignment
            b = std::move(tmp); // invokes move assignment
        }
        ```

        ```C++
        std::string str { "Knock" };    // use std::string because it is movable (std::string_view is not)
        std::vector<std::string> v;

        v.push_back(str); // calls l-value version of push_back => copies
        std::cout << "str: " << str << '\n';	// str is unchanged

        v.push_back(std::move(str)); // calls r-value version of push_back => moves
        std::cout << "str: " << str << '\n'; // ⚠️ str is now indeterminate
        ```
        👍 With a moved-from object (like `str`), it is safe to call any function that does not depend on the current value of the object.


## Smart pointer classes

* **Smart pointer**: a class that holds a pointer, and deallocates that pointer when the class object goes out of scope. ✅ => avoid memory leaks.
    ```C++
    void func1()
    {
        int* ptr { new int };

        return; // the function returns early, and ptr won’t be deleted!

        delete ptr;
    } // => memory leak
    ```

    ```C++
    template <typename T>
    class Auto_ptr     // "smart pointer"
    {
        T* m_ptr {};
    public:
        Auto_ptr(T* ptr=nullptr)
            :m_ptr(ptr)
        { }

        ~Auto_ptr() { delete m_ptr; }

        T& operator*() const { return *m_ptr; }
        T* operator->() const { return m_ptr; }
    };

    void func2()
    {
        Auto_ptr<int> ptr { new int };

        // no explicit delete here
    }   // ptr destructor will be called here
    ```
    ❌ `Auto_ptr` is critically flaw with shallow copy. Read more in github lesson.

* `std::unique_ptr`:
    * ✅ should be used to manage any **dynamically allocated object** that the ownership is not shared by multiple objects.
    * Properties:
        * ⚠️/✅ designed with move semantics in mind, copy initialization and copy assignment are disabled.
            ```C++
            std::unique_ptr<int> res1 { new int };  // resource created here
            std::unique_ptr<int> res2 { new int };  // Start as nullptr

            // res2 = res1; // Won't compile: copy assignment is disabled
	        res2 = std::move(res1); // res2 assumes ownership, res1 is set to null
            ```
        * has an overloaded `operator*` (returns a reference) and `operator->` (returns a pointer). ✅ Before we use either of these operators, we should check whether the `std::unique_ptr` actually has a resource. Because, ⚠️ it might be created empty, or the resource might have been moved elsewhere.
            ```C++
            std::unique_ptr<int> res{ new int { 6 } };

            if (res)    // make sure res contains a resource
            {
                std::cout << *res << '\n';  // dereference operator*
            }
            ```
    * ✅ It is okay to use `std::unique_ptr` with both scalar objects and arrays. It's smart enough. However, `std::array` or `std::vector` (or `std::string`) are almost always better choices.
    * ✅ `std::make_unique`: optional, but is preferred over creating `std::unique_ptr` yourself. It makes the code simpler, and resolves an exception safety issue.
        ```C++
        auto f1{ std::make_unique<int>(6) };    // create a dynamically allocated int with value 6
        auto f2{ std::make_unique<int[]>(4) };  // create a dynamically allocated array of int of length 4
        ```
    * Because  `std::unique_ptr` has move semantics, you should pass/return it by value.
        ```C++
        std::unique_ptr<std::string> createString()
        {
            return std::make_unique<std::string>("Knock");
        }

        void takeOwnership(std::unique_ptr<std::string> res) // pass by value to take ownership
        {
            if (res)
            ;
        } // res is destroyed here
        ```
    * If you don't want the function to take ownership of the resource - although you can pass it by const reference - it’s better to just pass the resource. Use `get()`:
        ```C++
        void useResource(const std::string* res)	// okay, just pass the resource
        {
            if (res)
            ;
        }

        auto res2{ std::make_unique<std::string>("Knock") };
        useResource(res2.get());
        ```
* `std::shared_ptr`:
    * is used when you need multiple smart pointers co-owning a resource. It keeps track of how many std::shared_ptr are sharing the resource and the resource will not be deallocated if at least one `std::shared_ptr` is pointing to it. As soon as the last `std::shared_ptr` goes out of scope (or is reassigned to point at something else), the resource will be deallocated.
        ```C++
        {
            int* res { new int };
            std::shared_ptr<int> ptr1{ res };
            {
                std::shared_ptr<int> ptr2 { ptr1 }; // make another std::shared_ptr from ptr1
            } // ptr2 goes out of scope here, but nothing happens
        } // ptr1 goes out of scope here, and the allocated int is destroyed
        ```
    * ❌ Don't create a second shared pointer from the resource directly
        ```C++
        {
            int* res { new int };
            std::shared_ptr<int> ptr1{ res };
            {
                std::shared_ptr<int> ptr2 { res }; // make another std::shared_ptr from res
            } // the allocated int is destroyed
        } // the allocated int is destroyed
        ```
    * `std::make_shared`: optional, but is preferred over creating `std::shared_ptr` yourself.
    * ⚠️ Circular dependencies and `std::weak_ptr`: See in github lesson.
    * A `std::unique_ptr` can be converted into a `std::shared_ptr`. However, `std::shared_ptr` can not be safely converted to a `std::unique_ptr`.
    * In C++17 and earlier, `std::shared_ptr` does not have proper support for managing arrays.


# Inheritance

* ⚠️ If `Derived` inherits from `Base`, then `Derived` is really 2 parts: a `Base` part, and a `Derived` part. When C++ constructs derived objects, it does so in phases: first, the most-base class is constructed, then **each** child class is constructed **in order** until the most-child class is constructed last.
    ```
       Derived object:
    -------------------
    |    Base part    |
    |                 |
    |     int m_x     |
    |-----------------|
    |  Derived part   |
    |                 |
    |     int m_y     |
    -------------------
    ```
* What actually happens when derived is instantiated:
    1. Memory for derived is set aside (enough for both the base and derived portions)
    2. The appropriate `Derived` constructor is called
    3. The `Base` object is constructed first using the appropriate Base constructor. 
      
        ⚠️ If no base constructor is specified, the **default base constructor** will be used.
    4. The member initializer list initializes variables
    5. The body of the constructor executes
    6. Control is returned to the caller

    ```C++
    class Base
    {
    public:
        int m_id {};

        Base(int id=1)
            : m_id { id }
        {
            std::cout << "Base\n";
        }
    };

    class Derived1: public Base
    {
    public:
        double m_cost {};

        Derived1(double cost=2)     // no base constructor is specified => will call default base constructor (Base(int id=1))
            : m_cost { cost }
        {
            std::cout << "Derived\n";
        }
    };

    Base base;
    Derived1 derived;
    ```
    This prints:
    ```
    Base
    Base
    Derived
    ```
* C++ prevents initializing **inherited** member variables in the member initializer list:
    ```C++
    Derived::Derived(int id, double cost)
        : m_id { id }       // error
        , m_cost { cost }
    { }
    ```

    ```C++
    Derived(double cost=0.0, int id=0)
        : Base{ id }        // okay, call Base(int) constructor
        , m_cost{ cost }
    { }
    ```
* Access specifiers:
    1. `public`: accessible by anybody
    2. `protected`: accessible base members, friends, and derived classes
    3. `private`: accessible by base members and friends, but not derived classes

    * C++ defaults to private inheritance.
    * The access specifier for an inherited member may be changed depending on the type of inheritance used:
        ```
        Base class's        |           Kind of inheritance
        access specifier    | Public       | Protected    | Private
        -----------------------------------------------------------------
        Public              | Public       | Protected    | Private
        Protected           | Protected    | Protected    | Private
        Private             | Inaccessible | Inaccessible | Inaccessible 
        ```
    * Overrided function does not inherit the access specifier in the base class.
        ```C++
        class Base
        {
        private:
            void print() {}
        };

        class Derived: public Base
        {
        public:
            void print() {}
        };
        ```
    * Given a set of overloaded functions in the base class, there is no way to change the access specifier for a single overload. You can only change them all.
        ```C++
        class Base
        {
        protected:
            void print(int)    { }
        };

        class Derived: public Base
        {
        public:
            using Base::print;  // change all Base::print overloads to public
        };
        ``` 
* Overloading resolution: 
    * ⚠️ First, **all** overloaded functions in the same class with that name are considered. If no overloaded functions are found, the search continues in the base class:
        ```C++
        class Base
        {
        public:
            void print(int)    { }
        };

        class Derived: public Base
        {
        public:
            void print(double) { }
        };

        Derived d{};
        d.print(5); // calls Derived::print(double), not Base::print(int)
        ```
    * What if we want to call `Base::print(int)` instead?
        * Option 1: Override
            ```C++
            class Derived: public Base
            {
            public:
                void print(int value)
                {
                    Base::print(value); // call Base::print(int)
                }
            };
            ```
        * Option 2: Use `using`. This tells the compiler to consider all `Base::print` functions when resolving print
            ```C++
            class Derived: public Base
            {
            public:
                using Base::print; 
                void print(double) { }
            };

            Derived d{};
            d.print(5); // calls Base::print(int)
            ```
* Hiding functionality: 
    * 2 options:
        1. mark member functions as `delete` in the derived class.
        2. change the access specifier in the derived class.
    * However, the base version of the function is still accessible:
        ```C++
        class Base
        {
        public:
            int getValue() const { }
        };

        class Derived : public Base
        {
        public:
            int getValue() const = delete;
        };

        Derived derived { 7 };

        derived.getValue();         // won't work
        derived.Base::getValue();   // call the Base::getValue() function directly
        static_cast<Base&>(derived).getValue();   // casting to a Base& (rather than a Base to avoid making a copy)
* Multiple inheritance: See code in github lesson.
* ⚠️ **Object slicing**: Consider this example:
    ```C++
    class Base
    {
    public:
        std::string_view getName() const { return "Base"; }
    };

    class Derived: public Base
    {
    public:
        std::string_view getName() const { return "Derived"; }
    };

    Derived derived {};
    ```

    * Pointers and references to the base **part** of derived objects:
        ```C++
        Base& rBase{ derived };    // reference to the base part of `derived`
        rBase.getName();            // call Base::getName(), not Derived::getName()

        Base* pBase{ &derived };   // pointer to the base part of `derived`
        pBase->getName();           // call Base::getName(), not Derived::getName()
        ```
        ⚠️ => A pointers/references to the base **part** can only see members of the base class.
    * Not using pointers/references might make a **copy** of the base part:
        ```C++
        Base base { derived };     // "copies" the Base portion of `derived` into `base`
        base.getName() << '\n';    // base is a Base, always calls Base::getName()
        ```

        ⚠️ The Frankenobject:
        ```C++
        Derived d1 {};
        Derived d2 {};
        Base& b{ d1 };
        b = d2;
        ```
        Here is what happens in the above code: Because `b` is a `Base`, and `operator=` is not virtual by default => only the `Base` part of `d2` is copied into `d1`, while the `Derived` part of `d1` remains unchanged => `d1` is now a Frankenobject: composed of parts of multiple objects.

        ⚠️ Sliding vectors:
        ```C++
        std::vector<Base6> v{};
        v.push_back(Base6{});    // add a Base object to our vector
        v.push_back(Derived6{}); // add a Derived object to our vector => sliced

        for (const auto& element : v)
            std::cout << "I am a " << element.getName() << '\n';
            // Outputs:
            // I am a Base
            // I am a Base
        ```
        => ✅ use pointers or references wrapper (See code in github lesson).
* Virtual functions and polymorphism:
    * A virtual function, when called, resolves to the **most-derived** version of the function for the **actual type** of the object being referenced or pointed to. Consider this example:
        ```C++
        class Base
        {
        public:
            std::string_view getName() const { return "Base"; }
        };

        class Derived: public Base
        {
        public:
            std::string_view getName() const { return "Derived"; }
        };

        Derived derived {};
        ```

        ```C++
        Base& rBase{ derived };   // reference to the Base part
        rBase.getName();  // normally resolve to Base::getName(), but because it's virtual, it calls Derived::getName()

        Base base { derived };    // ⚠️ not reference => copies the Base part
        base.getName();           // => call Base::getName(), not Derived::getName() although getName() is virtual
        ```
        ⚠️ => Virtual function resolution only works when a member function is called through a pointer/reference.
    * To call the Base version of a virtual function from a derived class, use the scope resolution operator:
        ```C++
        rBase.Base::getName(); // calls Base::getName()
        ```
    * If a function is virtual, all matching overrides in derived classes are also **implicitly** virtual.
    * ⚠️ A virtual function is only overrided if its signature and return types match exactly:
        ```C++
        class A1
        {
            virtual std::string_view getName1(int x) { return "A"; }
	        virtual std::string_view getName2(int x) { return "A"; }
        };

        class B1 : public A1
        {
            virtual std::string_view getName1(short x) { return "B"; } // not override: parameter is a short
            virtual std::string_view getName2(int x) const { return "B"; } // not override: function is const
        };
        ```
        => ✅ Use `override` keyword to let the compiler check for you: it raises errors if:
        1. the base function is not virtual,
        2. or, the child function does not override a base function.
        ```C++
        class C1 : public A1
        {
        public:
            std::string_view getName1(short x) override { return "C"; } // compile error, function is not an override
            std::string_view getName2(int x) const override { return "C"; } // compile error, non-virtual member function cannot be marked as override
            std::string_view getName2(int x) override { return "C"; } // okay
        };
        ```
        
        * ⚠️ ***Covariant return types***: One special case where the compiler allows a **different** "return type" to still be considered an override: if the return type of a virtual function is a pointer or reference to a class type, then the overriding function may return a pointer or reference to a **derived** class:
        ```C++
        class Base3
        {
        public:
            virtual Base3* getThis() { std::cout << "called Base::getThis()\n"; return this; }
            void printType() { std::cout << "returned a Base\n"; }
        };

        class Derived3 : public Base3
        {
        public:
            // Normally override functions have to return objects of the same type as the base function
            // However, it's okay to return Derived* instead of Base* because Derived is derived from Base.
            Derived3* getThis() override { std::cout << "called Derived::getThis()\n";  return this; }
            void printType() { std::cout << "returned a Derived\n"; }
        };

        void func4()
        {
            Derived3 d{};
            Base3* b{ &d };
            d.getThis()->printType(); // calls Derived::getThis(), returns a Derived*, calls Derived::printType
            b->getThis()->printType(); // calls Derived::getThis(), returns a Base*, ⚠️ calls Base::printType because printType is not virtual
        }
        ```
    * Use `final` keyword if you don’t want someone to override a virtual function, or inherit from a class.
    * ⚠️ Call virtual functions from constructors or destructors:
        * If you call a virtual function from within the base class constructor, it will always resolve to the base class version of the function. Because, at that point, the derived class portion of the object has not yet been constructed.
        * Similarly, if you call a virtual function from within the base class destructor, it will always resolve to the base class version of the function. Because, at that point, the derived class portion of the object has already been destroyed.
    * ✅ Virtual destructors: Always declare destructors as virtual in base classes. Because, if your derived class allocates resources, you might need to deallocate them through the base class pointer in polymorphic use.
    * ⚠️ Unlike other functions, virtualizing the assignment operator really opens up a bag full of worms. => don’t do it.
* **Pure virtual functions** (**abstract functions**):
    * a special kind of virtual function that must be overridden in derived classes. It can have no body at all:
        ```C++
        class Base
        {
        public:
            virtual void doSomething() = 0; // pure virtual function
        };
        ```
    * A pure virtual function makes a class **abstract**.
    * You can provide definition for pure virtual function, but the definition must be outside the class declaration (not inline):
        ```C++
        class Base
        {
        public:
            virtual void doSomething() = 0; // pure virtual function
        };

        void Base::doSomething()
        {
            // ...
        }
        ```
* Diamond problem and virtual inheritance: See code in github lesson.
* Dynamic casting:
    * We know that C++ allows implicit conversion from derived class pointers/references to base class pointers/references. However, sometimes we want to convert base class pointers/references to derived class pointers/references.
        
        For example, sometimes we want to access some derived-class-specific functionality from a base-class pointer/reference:
        ```C++
        class Base {};
        class Derived: public Base {}
        
        Base* getObject(bool returnDerived)
        {
            if (returnDerived)
                return new Derived{};
            else
                return new Base{};
        }

        Base* b { getObject(true) };

        // Now we want to call some Derived-specific function on b

        delete b;
        ```

        1. Solution 1: use virtual functions. But this might pollute the base class interface with functions that are only relevant to certain derived classes.
        2. Solution 2: use `dynamic_cast` to safely downcast base class pointers/references to derived class pointers/references.
    * `dynamic_cast`:
        ```C++
        Derived* d1 { dynamic_cast<Derived*>(b) };

        if (d) // make sure d is non-null
        {
            // ...
        }
        ```

        When `dynamic_cast` will not work:
        * when `b` wasn’t pointing to a Derived object. In this case `dynamic_cast` will return a null pointer.
        * With protected or private inheritance.
        * For classes that do not declare or inherit any virtual functions (and thus don’t have a virtual table).
        * In certain cases involving virtual base classes.
    * Downcasting can also be done with `static_cast`. It's faster, but ⚠️ more dangerous because it does no runtime type checking.
    * New programmers are sometimes confused about when to use `static_cast` vs `dynamic_cast`. => ✅ use `static_cast` unless you’re downcasting.


## Exception handling

* `throw` keyword: used to signal that an exception or error has occurred.
    * You can throw any data type you wish:
        ```C++
        throw 7;                      // throw an int
        throw std::string("Error");   // throw a string
        throw MyException{};          // throw an object of user-defined type
        ```
* `catch` keyword: used to handle exceptions for a single data type:
    ```C++
    catch (int x)
    {
        // Handle an exception of type int here
    }
    ```

    ```C++
    catch (const MyException& e)    // use const reference to avoid making an unnecessary copy
    {
    }
    ```

    * `catch(...)` can be used to catch any exception type:
        ```C++
        catch (...)
        {
            // Handle any exception type here
        }
        ```
* `std::exception`: Many of the classes and operators in the standard library throw exception classes on failure, e.g.: `std::bad_alloc`, `std::bad_cast`, .... All these exception classes are derived from the base class `std::exception`:
    ```C++
    try
    {
        throw std::runtime_error("An error occurred");
    }
    catch (const std::exception& e) // catch any standard library exception
    {
        std::cout << "Standard exception: " << e.what() << '\n';
    }
    ```
* Stack unwinding:
    1. When a function throws an exception, the program will look for a catch block that can handle the exception.
    2. If a handler is not found in the current function, it will look in the calling function and so on up the call stack until it finds a catch block that can handle the exception, or no handler can be found.
        1. If a handler is found, the stack is unwound.
        2. If no handler is found, the stack might or might not be unwound. => local objects might not be destroyed => ⚠️ any cleanup expected upon destruction of said variables will not happen!
* If a constructor must fail for some reason, we can simply throw an exception because all class members are destructed when construction is aborted. However, given that the class’s destructor is never called in this case, what we should do if we’ve allocated resources in our constructor before the exception is thrown?
    1. Solution 1: wrap any code that can fail in a try block. ⚠️ But this adds a lot of clutter.
    2. Solution 2: wrap the resource allocations inside a class member (because (recall that) class members are destructed if the constructor fails). ⚠️ However, creating a custom class like to manage a resource allocation isn’t efficient.
    3. Solution 3: ✅ use RAII-compliant classes such as files (`std::fstream`), smart pointers (`std::unique_ptr`, ...).
* The lifetime of exceptions: The object being thrown is typically a temporary object or a local variable. But recall that when a function throws an exception, the stack is unwound, causing all variables local to the function to be destroyed. So how can the object being thrown persist after the function has been exited?
    
    ⚠️ The answer is that the object is **copied** to some piece of memory (outside the stack) => the object being thrown generally need to be copyable. 
* Rethrowing an exception:
    * The wrong way:

        Remind: when we throw an exception, the thrown exception is copy-initialized from variable exception.
        ```C++
        class Base
        {
            virtual void print() { std::cout << "Base"; }
        };

        class Derived: public Base
        {
            void print() override { std::cout << "Derived"; }
        };

        try
        {
            try
            {
                throw Derived{};    // throw a copy of Derived
            }
            catch (Base& b)         // b is a Base reference to the (copied) Derived object
            {
                b.print();          // prints "Derived"
                throw b;            // ⚠️ throw a copy of the Base part of the Derived object!!!
            }
        }
        catch (Base& b)
        {
            b.print();              // prints "Base"!!!
        }
        ```
    * The right way: simply use the throw keyword from within the catch block with no associated variable
        ```C++
        try
        {
            try
            {
                throw Derived{};    
            }
            catch (Base& b)
            {
                b.print();          // prints "Derived"
                throw;              // rethrow the current exception without slicing
            }
        }
        catch (Base& b)
        {
            b.print();              // prints "Derived"!!!
        }
* **Function try block**: there is one particular case in which they are not sufficient:
    ```C++
    class A
    {
    public:
        A(int x)
        {
            if (x <= 0)
                throw 1; // Exception thrown here
        }
    };

    class B1 : public A
    {
    public:
        B1(int x) : A{x}
        {
            // What happens if creation of A fails and we want to handle it here?
        }
    };
    ```

    Function try block allows us to handle exceptions around the body of an entire function, rather than around a block of code.
    ```C++
    class B2 : public A
    {
    public:
        B2(int x) try : A{x}
        {
        }
        catch (...)
        {
            std::cerr << "Exception caught\n";

            throw; // rethrow the existing exception
        }
    };
    ```
    Notes:
    * A function-level catch block for a constructor must either throw a new exception or rethrow the existing exception -- they are not allowed to resolve exceptions!
    * Reaching the end of the catch block will implicitly rethrow.
* `noexcept`: 
    * In C++, all functions are classified as either:
        * potentially throwing: a function that might throw exceptions to its caller.
        * non-throwing: a function that is guaranteed not to throw exceptions to its caller. It can still throw exceptions internally but must catch and handle them itself internally. If a non-throwing function does throw an exception to its caller, `std::terminate` is called.
    * To define a function as non-throwing, we can use the `noexcept` specifier.
        ```C++
        void doSomething() noexcept {};
        ```
    * *Exception safety guarantees*: a contractual guideline about how functions or classes will behave when an exception occurs. 4 levels:
        1. No guarantee
        2. Basic guarantee: no resource leaks, but the program state may be modified.
        3. Strong guarantee: no resource leaks, and the program state is unchanged. => the function call is either completed successfully, or has no side effect.
        4. No-throw/no-fail guarantee: the function is guaranteed not to throw an exception to the caller (may throw internally). The `noexcept` specifier indicates this guarantee.
    * There are few good reasons to declare a function as `noexcept`:
        1. Non-throwing functions can be safely called from functions that are not exception-safe, such as destructors.
        2. Functions that are noexcept can enable the compiler to perform some optimizations.
        3. The standard library containers will use the `noexcept` operator to determine whether to use move semantics (faster) or copy semantics (slower).
* `std::move_if_noexcept`:
    * Consider the case where we are copying some object. If the copy fails for some reason, the object being copied is not harmed. However, if we move the object instead, and the move fails, ⚠️ the source object might be left in modified state.
    * `std::move_if_noexcept` is a counterpart to `std::move` that is used in the same way, but only performs the move if the object has a `noexcept` move constructor. Otherwise, it will return a copyable l-value.
        => ✅ We can use the `noexcept` specifier in conjunction with `std::move_if_noexcept` to provide strong exception safety guarantees.


## Static and dynamic libraries

* C++ library typically includes 2 pieces:
    1. Header files: contain declarations for the library’s functionality.
    2. Library files: contain the compiled implementation of the library’s functionality.
* C++ compilation process:
    1. Preprocessing: the output is still C++ code files.
    2. Compiler: the output is assembly code files (still human-readable).
    3. Assembler: the output is machine code (binary) files. The result is called **object files** (`.o` or `.obj`). However, these files are not yet executable.
    4. Linker: At this stage, we may have multiple object files:
        * some from our code
        * others from external libraries we included during development. 
        
        The linker's job is to combine all these object files into a single executable. There're 2 options:
        1. Static linking: all library code used by our program is copied into the final executable.
            * ✅ The final executable is self-contained and can be run on any system that supports the target architecture.
            * ⚠️ Think about how many programs on your system use the same `printf` function from the standard library. You'd end up with thousands of identical copies stored across your disk.
            * ❌ If a library is updated (e.g., to fix a bug), you need to recompile and relink all programs that use that library.
        2. Dynamic linking: libraries are pre-compiled into a special type of file called a **dynamic shared library** (`.so` files on Unix, `.dll` files on Windows). They are excutable files but don't contain a an entry point to start execution (the `main` function).  When our program is compiled, the linker won't copy the functions from the library directly into the executable. Instead, it will simply insert a reference to the library. At runtime, if the program needs a function from that dynamic library, the OS will load the required function into the program's address space so the program can use it as if it were part of the executable.
            * ✅ saves disk space
            * ✅ updating a shared library does not require recompiling or relinking the programs that use it.
* Why break the compilation process into so many phases if the compiler could just go directly from source to executable?
    * Suppose we need to write a program in C. But let's say we don't trust the compiler optimizations. So we decide to write the heavy calculation function directly in assembly and just call it from C. Then, when we pass both files to GCC, it will:
        1. compile and assemble the C code into an object file
        2. assemble the assembly code into another object file
        3. link both object files into a single executable file

        And voila, we've just compiled a multi-language project. This technique is used by real world systems like the Linux kernel, ffmpeg, openSSL, and many embedded projects.
    * Take Rust for example. It has a completely different tool chain from C, different compiler, different build system, and a different philosophy altogether. But same as C, Rust also relies on a linker. So if we want to call a Rust function from C:
        1. We compile the Rust code into an object file using Rust's compiler.
        2. We declare the Rust function in C, compile the C code into another object file using GCC.
        3. Finally, we link both object files into a single executable file using GCC.

        And of course, we can call C functions from Rust.

    * There's one more really important point to understand. Let's say we have two highle languages language A and language B. Just because both of them have a final linking phase doesn't automatically mean they can be correctly linked together into one executable. Even if both compilers emit assembly for the same architecture, they might make different assumptions (e.g, about how data is passed between functions, ...), resulting in unnexpected behavior. Therefore, the 2 sides must agree on a common rules, called the **application binary interface** (ABI).
* Installing and using libraries:
    * Installing:
        1. Acquire the library:
            * The best option iss to download a pre-compiled package.
            * Alternatively, you can download the source code and compile it yourself.

            On Linux, libraries are typically distributed as packages (e.g. .RPM). Your package manager may have some of the more popular libraries (e.g. SDL) listed already for easy installation, so check there first.
        2. Install the library: On Linux, this typically involves invoking the package manager and letting it do all the work.
        3. Tell the compiler where to find the library header files. On Linux, header files are typically installed to `/usr/include`.
        4. Tell the linker where to look for the library files. On Linux, library files are typically installed to `/usr/lib`.
    * Using: Once the library is installed and the IDE knows where to look for it, for each project that wants to use the library:
        5. If using static libraries or import libraries, tell the linker which library files to link.
        6. `#include` the library’s header files.
        7. If using dynamic libraries, tell your program where to find the dynamic library files at runtime. On Linux, library files are typically installed to `/usr/lib`. You can also set the `LD_LIBRARY_PATH` environment variable to point to additional directories. `LD_LIBRARY_PATH` contains a colon separated list of paths and the linker gives priority to these paths over the standard library paths `/lib` and `/usr/lib`. The standard paths will still be searched, but only after the list of paths in LD_LIBRARY_PATH has been exhausted.


---

Few reminders about passing temporary objects:
- they are created and initialized at the point of definition, 
  and are destroyed at the end of the full expression in which they are created.
- And evaluation of a temporary object is an rvalue expression.
- it will only bind to parameters that accept rvalues.
  This includes pass by value and pass by const reference, 
  and excludes pass by non-const reference and pass by address.




When passing arguments into a function by value, a copy of the argument is made.
- We encounter a similar situation when returning by value: a copy of the return value is passed back to the caller.




For non-extern constant global variables are visible from the point of declaration until the end of the "file" in which they are declared.


New programmers often think that creating variables is expensive.
- However, creating a variable has no cost.
- it is the initialization that has a cost, and there is typically 
  no cost difference between initialization and assignment. 
