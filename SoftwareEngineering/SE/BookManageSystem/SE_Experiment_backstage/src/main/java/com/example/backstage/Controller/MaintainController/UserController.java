package com.example.backstage.Controller.MaintainController;

import com.alibaba.fastjson.JSONObject;
import com.example.backstage.Entity.MaintainEntity.User;
import com.example.backstage.MD5Encryption;
import com.example.backstage.ResultVO;
import com.example.backstage.Service.MatainService.UserService;
import io.swagger.annotations.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletRequest;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

@Api("用户管理模块接口")
@Controller
@CrossOrigin
@RequestMapping("/maintain")
public class UserController {
    @Autowired
    UserService userService=new UserService();

    /**
     *
     * @param requestUser
     * @return
     */
    @RequestMapping(value = "/addUser",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("添加用户")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "user",value = "用户信息",required = true,paramType = "User"),
    })
    public ResultVO addUser(@RequestBody User requestUser){
        String id=requestUser.getId();
        String name=requestUser.getName();
        String sex=requestUser.getSex();
        String major=requestUser.getMajor();
        String uclass=requestUser.getUclass();
        String borrowid=requestUser.getBorrowid();
        int borrowNum=Integer.valueOf(requestUser.getBorrowNum());
        String pwd=requestUser.getPwd();
        int role=Integer.valueOf(requestUser.getRole());
        int penalty=0;
        User user=new User(id,name,sex,major,uclass,borrowid,borrowNum,pwd,role,penalty);
        if(userService.findId(id)!=null){
            return ResultVO.FAIL("学号已存在!");
        }else if (userService.findName(name)!=null){
            return ResultVO.FAIL("名字已存在!");
        }else if (userService.findBorrowId(borrowid)!=null){
            return ResultVO.FAIL("借书号已存在!");
        }else {
             userService.addUser(user);
             return ResultVO.SUCCESS("添加成功!");
        }
    }

    /**
     *
     * @param user
     * @return
     */
    @RequestMapping(value = "/updateUser",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation(value = "修改用户信息")
    @ApiParam(name = "user",value = "用户信息",required = true)
    public ResultVO updateUser(@RequestBody User user) {
        userService.updateUser(user);
        return ResultVO.SUCCESS("修改成功");
    }

    /**
     *
     * @param requestUser
     * @return
     */
    @RequestMapping(value = "/login",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("登录接口")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "user",value = "用户信息",required = true,paramType = "User"),
    })
    public ResultVO login(@RequestBody User requestUser){
        String id=requestUser.getId();
        String pwd=requestUser.getPwd();
        System.out.println(pwd);
        User user=userService.findId(id);
        if (user==null){
            return ResultVO.FAIL("账号不存在!");
        }else if (!MD5Encryption.getSaltVerifyMD5(user.getPwd(),MD5Encryption.getSaltMD5(pwd))){
            return ResultVO.FAIL("密码错误!");
        }else {
            return ResultVO.SUCCESS(user);
        }
    }


    /**
     *
     * @param user
     * @return
     */
    @RequestMapping(value = "/deleteUser",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation(value = "删除用户")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "id",value = "用户id",required = true,paramType = "User"),
    })
    public ResultVO deleteUser(@RequestBody User user){
        String id=user.getId();
        try {
            userService.deleteUser(id);
            return ResultVO.SUCCESS("删除成功!");
        }catch (Exception e){
            return ResultVO.FAIL("删除失败!");
        }
    }

    /**
     *
     * @param
     * @return
     */
    @RequestMapping(value = "/queryUserByName",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation(value = "通过名字查找用户")
    @ApiImplicitParam(name = "user",value = "用户信息",required = true)
    public ResultVO queryUserByName(@RequestBody JSONObject object){
        String name=object.getString("name");
        int page=Integer.valueOf(object.getString("page"));
        int size=Integer.valueOf(object.getString("size"));
        Pageable pageable=new PageRequest(page,size);
        Page<User> list=userService.findNameLike(name,pageable);
        if (list.getTotalElements()==0){
            return ResultVO.SUCCESS();
        }else {
            return ResultVO.SUCCESS(list);
        }
    }

    /**
     *
     * @return
     */
    @RequestMapping(value = "/queryOverdue",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("查询超期")
    public ResultVO queryOverdu(){
        List<String> idList=userService.findAllOverdue();
        List<User> userList=new ArrayList<>();
        for (int i=0;i<idList.size();i++){
            String id=idList.get(i);
            userList.add(userService.findId(id));
        }
        if (userList.size()==0){
            return ResultVO.FAIL("暂无超期读者!");
        }else {
            return ResultVO.SUCCESS(userList);
        }
    }


}
