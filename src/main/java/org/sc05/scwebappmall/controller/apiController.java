package org.sc05.scwebappmall.controller;


import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@SpringBootApplication
public class apiController {
    @GetMapping("/api/search-product")
    public String searchProduct() {return "Test";}
}
