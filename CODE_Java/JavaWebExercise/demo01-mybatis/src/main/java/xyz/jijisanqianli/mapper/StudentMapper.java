package xyz.jijisanqianli.mapper;

import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import xyz.jijisanqianli.pojo.Student;

import java.util.List;

@Mapper
public interface StudentMapper {
    @Select("select * from student")
    public List<Student> selectAll();


}
