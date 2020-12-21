package com.example.backstage.Controller.WebSearchController;

import com.example.backstage.Entity.MaintainEntity.Book;
import com.example.backstage.ResultVO;
import com.example.backstage.Service.MatainService.BookService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import net.minidev.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

@Controller
@RequestMapping("/search")
@Api("检索模块")
@CrossOrigin
public class SearchController {
     @Autowired
     private BookService service;

    @RequestMapping(value = "/queryAllBook",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("查询书籍")
    @ApiImplicitParam(name = "param",value = "具体参数",required = true)
    public ResultVO queryBook(@RequestBody JSONObject object){
        String all=object.getAsString("all");
        String name=object.getAsString("name");
        String author=object.getAsString("author");
        int page=Integer.valueOf(object.getAsString("page"));
        int size=Integer.valueOf(object.getAsString("size"));
        Pageable pageable=new PageRequest(page,size);
        if (all!=null){
            Page<Book> list=service.findAllByAll(all,pageable);
            if (list.getTotalElements()==0){
                return ResultVO.SUCCESS();
            }else {
                return ResultVO.SUCCESS(list);
            }
        }else if (name!=null){
            Page<Book> list=service.findAllByPage(name,pageable);
            if (list.getTotalElements()==0){
                return ResultVO.SUCCESS();
            }else {
                return ResultVO.SUCCESS(list);
            }
        }else if (author!=null){
            Page<Book> list=service.findAllByAuthor(author,pageable);
            if (list.getTotalElements()==0){
                return ResultVO.SUCCESS();
            }else {
                return ResultVO.SUCCESS(list);
            }
        }
        return ResultVO.FAIL();
    }
}
