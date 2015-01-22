package editor;

import java.util.Arrays;
import java.util.List;

import org.eclipse.jdt.core.dom.AST;
import org.eclipse.jdt.core.dom.ASTVisitor;
import org.eclipse.jdt.core.dom.Block;
import org.eclipse.jdt.core.dom.BodyDeclaration;
import org.eclipse.jdt.core.dom.Javadoc;
import org.eclipse.jdt.core.dom.MethodDeclaration;
import org.eclipse.jdt.core.dom.Modifier;
import org.eclipse.jdt.core.dom.PrimitiveType;
import org.eclipse.jdt.core.dom.SimpleName;
import org.eclipse.jdt.core.dom.SingleVariableDeclaration;
import org.eclipse.jdt.core.dom.TagElement;
import org.eclipse.jdt.core.dom.TextElement;
import org.eclipse.jdt.core.dom.Type;
import org.eclipse.jdt.core.dom.TypeDeclaration;
import org.eclipse.jdt.core.dom.Modifier.ModifierKeyword;

public class MethodAddVisitor extends ASTVisitor {

    @SuppressWarnings("unchecked")
    @Override
    public boolean visit(TypeDeclaration node) {
        List<BodyDeclaration> member = node.bodyDeclarations();
        member.add(createMethodDeclaration(node.getAST()));
        return super.visit(node);
    }

    @SuppressWarnings("unchecked")
    private MethodDeclaration createMethodDeclaration(AST ast) {
        MethodDeclaration method = ast.newMethodDeclaration();
        method.setName(newName(ast));
        method.modifiers().addAll(newModifiers(ast));
        method.setReturnType2(newReturnType(ast));
        method.parameters().addAll(newParameters(ast));
        method.thrownExceptions().addAll(newThrownExceptions(ast));
        method.setBody(newBody(ast));
        method.setJavadoc(newJavadoc(ast));
        return method;
    }

    private SimpleName newName(AST ast) {
        return ast.newSimpleName("newMethod");
    }

    private List<Modifier> newModifiers(AST ast) {
        return Arrays.asList(ast.newModifier(ModifierKeyword.PUBLIC_KEYWORD));
    }

    private Type newReturnType(AST ast) {
        return ast.newPrimitiveType(PrimitiveType.INT);
    }

    private List<SingleVariableDeclaration> newParameters(AST ast) {
        SingleVariableDeclaration param = ast.newSingleVariableDeclaration();
        param.setName(ast.newSimpleName("param"));
        param.setType(ast.newSimpleType(ast.newName("String")));
        return Arrays.asList(param);
    }

    private List<SimpleName> newThrownExceptions(AST ast) {
        return Arrays.asList(ast.newSimpleName("Exception"));
    }

    private Block newBody(AST ast) {
        return ast.newBlock();
    }

    @SuppressWarnings("unchecked")
    private Javadoc newJavadoc(AST ast) {
        TextElement text = ast.newTextElement();
        text.setText("This is a new method!");
        TagElement textTag = ast.newTagElement();
        textTag.fragments().add(text);

        TagElement paramTag = ast.newTagElement();
        paramTag.setTagName("@param");

        TagElement returnTag = ast.newTagElement();
        returnTag.setTagName("@return");

        Javadoc javadoc = ast.newJavadoc();
        javadoc.tags().addAll(Arrays.asList(textTag, paramTag, returnTag));
        return javadoc;
    }

}
