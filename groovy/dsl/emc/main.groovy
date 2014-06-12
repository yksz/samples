def runDSL(path) {
    def script = new GroovyShell().parse(new File(path))
    script.metaClass = createEMC(script.class) { emc ->
        emc.pet = { closure ->
            def pet = new Pet()
            closure.delegate = pet
            closure.resolveStrategy = Closure.DELEGATE_ONLY
            closure()
            println pet
        }
    }
    script.run()
}

def createEMC(Class clazz, Closure closure) {
    def emc = new ExpandoMetaClass(clazz, false)
    closure(emc)
    emc.initialize()
    return emc
}

runDSL("dsl.groovy")
