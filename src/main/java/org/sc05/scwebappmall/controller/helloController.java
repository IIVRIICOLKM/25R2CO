package org.sc05.scwebappmall.controller;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
@RestController
@SpringBootApplication
public class helloController {
    @RequestMapping("/home")
    public String home() {
        return "Hello World";
    }
    //react axios test api
    @GetMapping("/api/test")
    public String hello() {
        return "테스트입니다.";
    }

}
