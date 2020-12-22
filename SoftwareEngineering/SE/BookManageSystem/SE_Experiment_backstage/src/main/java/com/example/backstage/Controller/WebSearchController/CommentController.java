package com.example.backstage.Controller.WebSearchController;

import com.example.backstage.Entity.MaintainEntity.User;
import com.example.backstage.Entity.WebSearchEntity.Comment;
import com.example.backstage.ResultVO;
import com.example.backstage.Service.WebSearchService.CommentService;
import io.swagger.annotations.*;
import net.minidev.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@Controller
@RequestMapping("/search")
@Api("留言管理")
@CrossOrigin
public class CommentController {
    @Autowired
    private CommentService service;

    /**
     *
     * @param comment
     * @return
     */
    @RequestMapping(value = "/addComment",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("添加留言")
    @ApiImplicitParam(name = "comment",value = "留言信息",required = true)
    public ResultVO addComment(@RequestBody Comment comment){
        Date date=new Date();
        comment.setPublishDate(date);
        try {
            service.addComment(comment);
            return ResultVO.SUCCESS("添加成功!");
        }catch (Exception e){
            return ResultVO.FAIL("添加失败!");
        }
    }

    /**
     *
     * @param object
     * @return
     */
    @RequestMapping(value = "/queryAllComment",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("查询所有留言")
    @ApiImplicitParam(name = "param",value = "页数及大小",required = true)
    public ResultVO queryAll(@RequestBody JSONObject object){
         int page=Integer.valueOf(object.getAsString("page"));
        int size=Integer.valueOf(object.getAsString("size"));
        Pageable pageable=new PageRequest(page,size);
        Page<Comment> commentList=service.findAllByPage(pageable);
        if (commentList.getTotalElements()==0){
            return ResultVO.SUCCESS();
        }else {
            return ResultVO.SUCCESS(commentList) ;
        }
    }

    /**
     *
     * @param comment
     * @return
     */
    @RequestMapping(value = "/deleteComment",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("删除留言")
    @ApiImplicitParam(name = "id",value = "留言id",required = true)
    public ResultVO deleteComment(@RequestBody Comment comment){
        int id=comment.getId();
        try {
            service.deleteComment(id);
            return ResultVO.SUCCESS("删除成功!");
        }catch (Exception e){
            return ResultVO.FAIL("删除失败!");
        }
    }
}
