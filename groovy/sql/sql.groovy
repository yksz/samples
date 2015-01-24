@GrabConfig(systemClassLoader=true)
@Grab(group='com.h2database', module='h2', version='1.4.+')
import groovy.sql.Sql

def config = 'h2.properties'
if (args.length > 0)
    config = args[0]
println "$config"

def db = new Properties()
new File(config).withInputStream {
    db.load(it)
}

def sql = Sql.newInstance(db.url, db.user, db.password, db.driver)
sql.execute '''
    create table PROJECT (
        id integer not null,
        name varchar(50),
        url varchar(100)
    )
'''
def params = [10, 'Groovy', 'http://groovy.codehaus.org']
sql.execute 'insert into PROJECT (id, name, url) values (?, ?, ?)', params
sql.eachRow('select * from PROJECT') { row ->
    println "${row.name.padRight(10)} ($row.url)"
}
sql.close()
