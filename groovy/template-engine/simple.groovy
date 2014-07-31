long start = System.currentTimeMillis()

def binding = [
    firstname : "Grace",
    lastname  : "Hopper",
    accepted  : true,
    title     : 'Groovy for COBOL programmers'
]
def engine = new groovy.text.SimpleTemplateEngine()
def text = '''\
Dear <%= firstname %> $lastname,

We <% if (accepted) print 'are pleased' else print 'regret' %> \
to inform you that your paper entitled
'$title' was ${ accepted ? 'accepted' : 'rejected' }.

The conference committee.
'''
def template = engine.createTemplate(text).make(binding)
println template.toString()

long stop = System.currentTimeMillis()
println "${(stop - start) / 1000} sec"
