package com.example.backstage.Controller.CatalogueController;

import com.example.backstage.Entity.CatalogueEntity.Damage;
import com.example.backstage.ResultVO;
import com.example.backstage.Service.CatalogueService.DamageService;
import com.example.backstage.Service.MatainService.BookService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import net.minidev.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.sql.ResultSet;

@Controller
@RequestMapping("/damage")
@Api("报销注损模块")
@CrossOrigin
public class DamageController {
    @Autowired
    private DamageService damageService;
    @Autowired
    private BookService bookService;

    @RequestMapping(value = "/queryDamage",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("查询报损图书")
    @ApiImplicitParam(name = "param",value = "具体参数",required = true)
    public ResultVO queryDamage(@RequestBody JSONObject object){
        String name=object.getAsString("name");
        int page=Integer.valueOf(object.getAsString("page"));
        int size=Integer.valueOf(object.getAsString("size"));
        Pageable pageable=new PageRequest(page,size);
        Page<Damage> list=damageService.findAll(name,pageable);
        if (list.getTotalElements()==0){
            return ResultVO.SUCCESS();
        }else {
            return ResultVO.SUCCESS(list);
        }
    }

    @RequestMapping(value = "/addDamage",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("添加报损图书")
    @ApiImplicitParam(name = "param",value = "具体参数",required = true)
    public ResultVO addDamage(@RequestBody Damage damage){
        String isbn=damage.getIsbn();
        if (damageService.findByIsbn(isbn)!=null){
            return ResultVO.SUCCESS("此书籍已添加至报损列表!");
        }else if (bookService.findByIsbn(isbn)==null){
            return ResultVO.SUCCESS("不存在此书!");
        }
        else {
            damageService.addDamage(damage);
            return ResultVO.SUCCESS("添加成功!");
        }
    }

    @RequestMapping(value = "/updateDamage",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("更新报损图书")
    @ApiImplicitParam(name = "param",value = "具体参数",required = true)
    public ResultVO updateDamage(@RequestBody Damage damage){
        damageService.addDamage(damage);
        return ResultVO.SUCCESS("修改成功!");
    }

    @RequestMapping(value = "/deleteDamage",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("注销图书")
    @ApiImplicitParam(name = "param",value = "具体参数",required = true)
    public ResultVO deleteDamage(@RequestBody Damage damage){
        String isbn=damage.getIsbn();
        try {
            damageService.deleteByIsbn(isbn);
            bookService.deleteByIsnb(isbn);
            return ResultVO.SUCCESS("注销成功!");
        }catch (Exception e){
            return ResultVO.FAIL();
        }
    }
}
