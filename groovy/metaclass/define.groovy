Integer.metaClass.define {
    reverse = {
        return delegate.toString().reverse() as Integer
    }
}

println 123456.reverse()
