package com.project.assignement2;

public enum ParamParts {
    STATE(0),
    NPROD(1),
    NTEST(2);

    private int value;

    ParamParts(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }
}
