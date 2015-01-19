package editor;

import java.util.List;

import org.eclipse.jdt.core.dom.ASTVisitor;
import org.eclipse.jdt.core.dom.Javadoc;
import org.eclipse.jdt.core.dom.MethodDeclaration;
import org.eclipse.jdt.core.dom.TagElement;

class MethodDeleteVisitor extends ASTVisitor {

    @Override
    public boolean visit(MethodDeclaration node) {
        deleteMethod(node, "@deprecated");
        return super.visit(node);
    }

    @SuppressWarnings("unchecked")
    private void deleteMethod(MethodDeclaration node, String javadocTag) {
        Javadoc javadoc = node.getJavadoc();
        if (javadoc == null)
            return;
        List<TagElement> elems = javadoc.tags();
        for (TagElement elem : elems) {
            String tagName = elem.getTagName();
            if (tagName == null)
                continue;
            if (tagName.equals(javadocTag)) {
                node.delete();
                return;
            }
        }
    }

}
