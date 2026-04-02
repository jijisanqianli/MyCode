package com.lyj.controller;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class Hello {
    @RequestMapping("/hello")
    public String HelloWeb(User user){
        String x = "Hello Web~~~ " + "年龄为"+user.getAge()+"的"+user.getName();
        System.out.println(x);
        System.out.println(user.toString());
        return x;
    }

    @RequestMapping("/address")
    public Address getaddress(Address address){
        return address;
    }

}
