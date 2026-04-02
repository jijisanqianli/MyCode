package com.lyj.job0111.controller;

import com.lyj.job0111.pojo.Result;
import com.lyj.job0111.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;


@RestController
@RequestMapping("/user")
public class UserController {

    @Autowired
    private UserService userService;

    @PostMapping("/login")
    public Result login(String username, String password) {
        String res = userService.login(username, password);
        if (res.equals("登录成功") || res.equals("注册成功")) {
            return Result.success(res);
        }
        return Result.fail();
    }
}
