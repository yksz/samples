import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DatabaseMetaData;

import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sql.DataSource;

public class DataSourceServlet extends HttpServlet {

    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws IOException, ServletException {
        try {
            DataSource ds = InitialContext.doLookup("java:comp/DefaultDataSource");
            Connection conn = ds.getConnection();
            DatabaseMetaData metaData = conn.getMetaData();
            PrintWriter writer = resp.getWriter();
            writer.println("DatabaseProductName: " + metaData.getDatabaseProductName());
            writer.println("DatabaseProductVersion: " + metaData.getDatabaseProductVersion());
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

}
