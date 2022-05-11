module com.project.assignement2 {
    requires javafx.controls;
    requires javafx.fxml;

        requires org.controlsfx.controls;
    requires javafx.graphics;
    requires jssc;

    opens com.project.assignement2 to javafx.fxml;
    exports com.project.assignement2;
}