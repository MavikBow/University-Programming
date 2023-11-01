module com.example.javafxnewyearshop {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.javafxnewyearshop to javafx.fxml;
    exports com.example.javafxnewyearshop;
}