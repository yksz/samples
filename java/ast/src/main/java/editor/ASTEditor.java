package editor;

import java.io.File;

import org.apache.commons.io.FileUtils;
import org.eclipse.core.runtime.NullProgressMonitor;
import org.eclipse.jdt.core.dom.AST;
import org.eclipse.jdt.core.dom.ASTParser;
import org.eclipse.jdt.core.dom.ASTVisitor;
import org.eclipse.jdt.core.dom.CompilationUnit;
import org.eclipse.jface.text.BadLocationException;
import org.eclipse.jface.text.Document;
import org.eclipse.text.edits.MalformedTreeException;
import org.eclipse.text.edits.TextEdit;

public class ASTEditor {

    public String edit(String sourceCode, ASTVisitor... visitors)
            throws MalformedTreeException, BadLocationException {
        Document doc = new Document(sourceCode);
        ASTParser parser = ASTParser.newParser(AST.JLS4);
        parser.setSource(doc.get().toCharArray());
        CompilationUnit unit = (CompilationUnit) parser.createAST(new NullProgressMonitor());
        unit.recordModifications();

        for (ASTVisitor visitor : visitors) {
            unit.accept(visitor);
        }

        TextEdit edit = unit.rewrite(doc, null);
        edit.apply(doc);
        return doc.get();
    }

    public String format(String sourceCode) {
        return sourceCode.replaceAll("\t", "    ");
    }

    public static void main(String[] args) throws Exception {
        ASTEditor editor = new ASTEditor();
        String sourceCode = FileUtils.readFileToString(new File("res/Hoge.java"));
        String modifiedSourceCode = editor.edit(sourceCode,
                new MethodAddVisitor(), new MethodDeleteVisitor());

        System.out.println("##### Before #####");
        System.out.println(sourceCode);
        System.out.println("##### After #####");
        System.out.println(editor.format(modifiedSourceCode));
    }

}
