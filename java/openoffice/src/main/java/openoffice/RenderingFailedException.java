package openoffice;

public class RenderingFailedException extends Exception {

    private static final long serialVersionUID = 8160533829869187234L;

    public RenderingFailedException() {
        super();
    }

    public RenderingFailedException(String message) {
        super(message);
    }

    public RenderingFailedException(String message, Throwable cause) {
        super(message, cause);
    }

    public RenderingFailedException(Throwable cause) {
        super(cause);
    }

}
