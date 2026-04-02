package com.lyj.job0101.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class LoginPageController {
    @RequestMapping("/loginPage")
    public String login() {
        return "redirect:/login_page.html";
    }
}
