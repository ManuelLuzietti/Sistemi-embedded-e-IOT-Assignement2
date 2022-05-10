package com.project.assignement2;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import com.project.assignement2.ParamParts;
import javafx.scene.input.MouseEvent;

public class ViewController {

    @FXML
    private TextField nSelfTest;

    @FXML
    private TextField nprodLabel;

    @FXML
    private Button recoverButton;

    @FXML
    private Button refillButton;

    @FXML
    private TextField stateLabel;
    private CoffeeMachineManager manager;

    public void setParams(String[] params) {
        stateLabel.setText(params[ParamParts.STATE.getValue()]);
        //System.out.println(params[ParamParts.STATE.getValue()]);
        nprodLabel.setText(params[ParamParts.NPROD.getValue()]);
        nSelfTest.setText(params[ParamParts.NTEST.getValue()]);
    }
    public  void initialize(CoffeeMachineManager manager){
        this.manager = manager;
    }
    @FXML
    void recoverClicked(MouseEvent event) {
        manager.recoverClickedEventHandler();
    }

    @FXML
    void refillClicked(MouseEvent event) {
        manager.refillClickedEventHandler();
    }

}
