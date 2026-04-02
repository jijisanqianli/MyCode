package com.lyj.job0111.dao;

import com.lyj.job0111.pojo.User;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface UserMapper {
    //实现查询功能
    @Select("select * from user where username=#{username}")
    User getUserByUsername(String username);
    //实现注册功能
    @Insert("insert into user (username,password) values (#{username},#{password})")
    void registerNewUser(String username,String password);
}
