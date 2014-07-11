import groovy.transform.*

@Field List awe = [1, 2, 3]
def awesum() { awe.sum() }
assert awesum() == 6
