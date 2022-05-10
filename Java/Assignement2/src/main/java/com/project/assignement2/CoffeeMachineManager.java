package com.project.assignement2;

import javafx.animation.PauseTransition;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.io.IOException;
import java.util.Arrays;
import java.util.concurrent.ScheduledExecutorService;

public class CoffeeMachineManager extends Application {
    private CommChannel channel;
    @Override
    public void start(Stage stage) throws Exception {
        channel = new SerialCommChannel("COM3", 9600);
        System.out.println("Waiting Arduino for rebooting...");
        Thread.sleep(5000);
        System.out.println("Ready.");
        FXMLLoader fxmlLoader = new FXMLLoader(this.getClass().getResource("/com/project/assignement2/fxml/mainWindow.fxml"));
        Scene scene = fxmlLoader.load();
        ViewController controller = (ViewController) fxmlLoader.getController();
        controller.initialize(this);
        stage.setTitle("Coffee Machine Manager");
        stage.setScene(scene);
        stage.show();
        PauseTransition transition = new PauseTransition(Duration.millis(500));

        new Thread() {
            @Override
            public void run() {
                super.run();
                while (true) {

                    try {
                        if (channel.isMsgAvailable()) {
                            String msg = channel.receiveMsg();
                            System.out.println(msg);
                            String[] params = msg.split(" ");
                            if(params.length != 3){
                                continue;
                            }
                            System.out.println(Arrays.stream(params).toList());
                            controller.setParams(params);
                        }
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }.start();
    }
    public void refillClickedEventHandler(){
        channel.sendMsg("1");
    }
    public void recoverClickedEventHandler(){
        channel.sendMsg("2");
    }
    public static void main(String[] args) {
        launch();
    }
}