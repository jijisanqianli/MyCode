package com.lyj.job0101.controller;

import com.lyj.job0101.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashMap;
import java.util.Map;

@RestController
public class LoginController {
    @Autowired
    private UserService userService;

    @RequestMapping("/login")
    public Map<String, Object> result(String username,String password){
        String result=userService.usernameOrRegister(username,password);
        Map<String, Object> map= new HashMap<>();

        if ("登录成功".equals(result)) {
            map.put("code", 200);
            map.put("msg", "登录成功");
        }
        else if ("已注册新用户，登录成功".equals(result)) {
            map.put("code", 200);
            map.put("msg", "已注册新用户，登录成功");
        }
        else {
            map.put("code", 404);
            map.put("msg", "登录失败");
        }
        return map;
    }
}
