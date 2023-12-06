module com.example.javafxnewyear2 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;


    opens com.example.javafxnewyearshop to javafx.fxml;
    exports com.example.javafxnewyearshop;
}