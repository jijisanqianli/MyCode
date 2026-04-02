package com.lyj.job0101.service;

import com.lyj.job0101.dao.UserMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import com.lyj.job0101.pojo.User;

@Service
public class UserService {
    @Autowired
    private UserMapper userMapper;

    public String usernameOrRegister(String username,String password){
        if (username == null || username.isEmpty() || password == null || password.isEmpty()){
            return "参数为空";
        }
        User user=userMapper.getUserByUsername(username);
        if(user!=null){//存在用户名
            if(password.equals(user.getPassword())){//密码正确
                return "登录成功";
            }else{
                return "密码错误";
            }
        }else{//不存在用户，则注册该账号
            userMapper.registerNewUser(username,password);
            return "已注册新用户，登录成功";
        }
    }
}
