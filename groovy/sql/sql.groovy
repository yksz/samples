@Grab(group='com.h2database', module='h2', version='1.4.+')
import groovy.sql.Sql

def db = [
    url:'jdbc:h2:mem:testDB;MVCC=TRUE;LOCK_TIMEOUT=10000',
    user:'sa',
    password:'',
    driver:'org.h2.Driver'
]
def sql = Sql.newInstance(db.url, db.user, db.password, db.driver)
sql.execute '''
    create table PROJECT (
        id integer not null,
        name varchar(50),
        url varchar(100),
    )
'''
