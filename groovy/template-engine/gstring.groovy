long start = System.currentTimeMillis()

def binding = [
    firstname : "Grace",
    lastname  : "Hopper",
    accepted  : true,
    title     : 'Groovy for COBOL programmers'
]
def engine = new groovy.text.GStringTemplateEngine()
def text = '''\
Dear <%= firstname %> $lastname,

We <% if (accepted) out << 'are pleased' else out << 'regret' %> \
to inform you that your paper entitled
'$title' was ${ accepted ? 'accepted' : 'rejected' }.

The conference committee.
'''
def template = engine.createTemplate(text).make(binding)
println template.toString()

long stop = System.currentTimeMillis()
printl "${(stop - start) / 1000} sec"
