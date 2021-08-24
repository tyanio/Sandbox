package main

import (
	"testing"
)

func TestExampleSuccess(t *testing.T){
	result, err := example("hoge")
    if err != nil {
        t.Fatalf("failed test %#v", err)
    }
    if result != 1 {
        t.Fatal("failed test")
    }
}