#ifndef STACK_H
#define STACK_H

#include <cstddef>

/**
 *  スタックはコンテナアダプタの一種で,データをLIFO構造で保持します.
 */
template<typename T>
class Stack final {
public:
    /**
     * コンストラクタです.
     */
    Stack();

    /**
     * デストラクタです.
     */
    ~Stack();

    /**
     * スタックが空かどうかを返します.
     * すなわち,要素数が0かどうかを返します.
     *
     * @return 要素数が0であればtrue,そうでなければfalse
     * @see size()
     */
    bool empty();

    /**
     * 要素数を返します.
     *
     * @return 要素数
     */
    std::size_t size();

    /**
     * スタックの先頭要素への参照を返します.
     * スタックはLIFOなので,先頭要素はスタックに挿入された最後の要素です.
     *
     * @return スタックの先頭要素への参照
     */
    T& top();

    /**
     * スタックの先頭に新しい要素を挿入します.
     * 新しい要素の内容はvalのコピーで初期化されます.
     *
     * @param[in] val 挿入された要素が初期化される値
     */
    void push(const T& val);

    /**
     * スタックの先頭要素を削除します.
     * 削除された要素はスタックに挿入された最後の要素です.
     * その要素は top() を呼び出すことで取得できます.
     *
     * このメソッドは削除された要素のデストラクタを呼び出します.
     *
     * @see top()
     */
    void pop();
};

#endif // STACK_H
