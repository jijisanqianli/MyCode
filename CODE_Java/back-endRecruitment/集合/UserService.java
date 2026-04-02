package com.lyj.job0111.service;

import com.lyj.job0111.dao.UserMapper;
import com.lyj.job0111.pojo.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

@Service
public class UserService{

    @Autowired
    private UserMapper userMapper;

    // 加密工具
    private final BCryptPasswordEncoder encoder = new BCryptPasswordEncoder();

    public String login(String username, String password) {
        User user = userMapper.getUserByUsername(username);

        if (user == null) {
            // 注册，密码加密存储
            User newUser = new User();
            newUser.setUsername(username);
            newUser.setPassword(encoder.encode(password));
            userMapper.registerNewUser(newUser.getUsername(),newUser.getPassword());
            return "注册成功";
        }

        // 登录验证
        if (encoder.matches(password, user.getPassword())) {
            return "登录成功";
        } else {
            return "密码错误";
        }
    }
}
